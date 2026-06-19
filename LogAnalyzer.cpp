#include "LogAnalyzer.h"
#include "ThreadWorker.h"

#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <future>

/*
=========================================================
Log Analyzer

Loads log file

Splits into chunks

Processes chunks concurrently using std::async

Merges results
=========================================================
*/

Statistics LogAnalyzer::analyze(
    const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file)
    {
        throw std::runtime_error(
            "Cannot open log file."
        );
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    if (lines.empty())
    {
        return {};
    }

    constexpr size_t THREAD_COUNT = 4;

    std::vector<
        std::future<Statistics>
    > futures;

    const size_t chunkSize =
        (lines.size() + THREAD_COUNT - 1)
        / THREAD_COUNT;

    for (size_t i = 0;
         i < THREAD_COUNT;
         ++i)
    {
        const size_t start =
            i * chunkSize;

        if (start >= lines.size())
        {
            break;
        }

        const size_t end =
            std::min(
                start + chunkSize,
                lines.size()
            );

        std::vector<std::string> chunk(
            lines.begin() + start,
            lines.begin() + end
        );

        futures.push_back(
            std::async(
                std::launch::async,
                ThreadWorker::processChunk,
                chunk
            )
        );
    }

    Statistics globalStats;

    for (auto& future : futures)
    {
        Statistics local =
            future.get();

        globalStats.totalLines +=
            local.totalLines;

        globalStats.infoCount +=
            local.infoCount;

        globalStats.warningCount +=
            local.warningCount;

        globalStats.errorCount +=
            local.errorCount;

        for (const auto& pair :
             local.recurringErrors)
        {
            globalStats
                .recurringErrors[pair.first]
                += pair.second;
        }
    }

    if (globalStats.totalLines > 0)
    {
        globalStats.errorRate =
            (static_cast<double>(
                 globalStats.errorCount)
             / globalStats.totalLines)
            * 100.0;
    }

    return globalStats;
}
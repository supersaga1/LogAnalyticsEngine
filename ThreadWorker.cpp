#include "ThreadWorker.h"

#include <regex>

/*
=========================================================
Expected Format

2026-06-19 INFO Application Started

2026-06-19 ERROR Database Connection Failed

2026-06-19 WARNING Memory Usage High
=========================================================
*/

Statistics ThreadWorker::processChunk(
    const std::vector<std::string>& lines)
{
    Statistics stats;

    /*
    Capture:

    Group 1 -> Timestamp

    Group 2 -> Severity

    Group 3 -> Message
    */

    static const std::regex logPattern(
        R"((.*?)\s+(INFO|WARNING|ERROR)\s+(.*))"
    );

    std::smatch matches;

    for (const auto& line : lines)
    {
        stats.totalLines++;

        if (!std::regex_match(line, matches, logPattern))
        {
            continue;
        }

        const std::string severity = matches[2];
        const std::string message  = matches[3];

        if (severity == "INFO")
        {
            stats.infoCount++;
        }
        else if (severity == "WARNING")
        {
            stats.warningCount++;
        }
        else if (severity == "ERROR")
        {
            stats.errorCount++;

            /*
            Track recurring failures
            */
            stats.recurringErrors[message]++;
        }
    }

    if (stats.totalLines > 0)
    {
        stats.errorRate =
            (static_cast<double>(stats.errorCount)
             / stats.totalLines) * 100.0;
    }

    return stats;
}
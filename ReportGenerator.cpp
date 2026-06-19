#include "ReportGenerator.h"

#include <fstream>
#include <vector>
#include <algorithm>

/*
=========================================================
Generate Report

Produces:

- Counts
- Error Rate
- Top Failures
- Most Frequent Error
=========================================================
*/

void ReportGenerator::generate(
    const Statistics& stats,
    const std::string& outputFile)
{
    std::ofstream out(outputFile);

    if (!out)
    {
        return;
    }

    out << "====================================\n";
    out << "      LOG ANALYSIS REPORT\n";
    out << "====================================\n\n";

    out << "Total Lines : "
        << stats.totalLines
        << "\n";

    out << "INFO Count : "
        << stats.infoCount
        << "\n";

    out << "WARNING Count : "
        << stats.warningCount
        << "\n";

    out << "ERROR Count : "
        << stats.errorCount
        << "\n";

    out << "\nError Rate : "
        << stats.errorRate
        << " %\n\n";

    std::vector<
        std::pair<std::string, int>
    > errors(
        stats.recurringErrors.begin(),
        stats.recurringErrors.end()
    );

    std::sort(
        errors.begin(),
        errors.end(),
        [](const auto& a,
           const auto& b)
        {
            return a.second > b.second;
        }
    );

    out << "Top Recurring Errors\n";
    out << "---------------------\n";

    const size_t topCount =
        std::min(
            static_cast<size_t>(5),
            errors.size()
        );

    for (size_t i = 0;
         i < topCount;
         ++i)
    {
        out << errors[i].first
            << " : "
            << errors[i].second
            << "\n";
    }

    out << "\n";

    if (!errors.empty())
    {
        out << "Most Frequent Error\n";
        out << "-------------------\n";

        out << errors.front().first
            << " ("
            << errors.front().second
            << " occurrences)\n";
    }

    out << "\n====================================\n";
}
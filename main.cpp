#include "LogAnalyzer.h"
#include "ReportGenerator.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: analyzer <logfile>\n";
        return 1;
    }

    try
    {
        LogAnalyzer analyzer;
        Statistics stats = analyzer.analyze(argv[1]);

        ReportGenerator::generate(stats, "report.txt");

        std::cout << "Analysis complete.\n";
        std::cout << "Report generated: report.txt\n";
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}

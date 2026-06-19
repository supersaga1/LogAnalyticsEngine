#pragma once
#include "Statistics.h"
#include <string>

class ReportGenerator {
public:
    static void generate(const Statistics& stats,
                         const std::string& outputFile);
};

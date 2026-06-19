#pragma once
#include <string>
#include "Statistics.h"

class LogAnalyzer {
public:
    Statistics analyze(const std::string& filePath);
};

#pragma once

#include <unordered_map>
#include <string>

/*
=========================================================
Severity Levels

Using enum class instead of plain enums provides
strong type safety and is considered modern C++.
=========================================================
*/

enum class Severity
{
    Info,
    Warning,
    Error,
    Unknown
};

/*
=========================================================
Statistics

Stores all analytics generated during log processing.
=========================================================
*/

struct Statistics
{
    size_t totalLines = 0;

    size_t infoCount = 0;
    size_t warningCount = 0;
    size_t errorCount = 0;

    double errorRate = 0.0;

    /*
    Example:

    Database Connection Failed -> 12
    Network Timeout            -> 8
    */
    std::unordered_map<std::string, int> recurringErrors;
};
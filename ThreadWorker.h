#pragma once

#include <vector>
#include <string>

#include "Statistics.h"

/*
=========================================================
ThreadWorker

Responsible for processing a chunk of log lines.

Can later be executed using:
- std::thread
- std::async
- std::future
=========================================================
*/

class ThreadWorker
{
public:

    /*
    Process a chunk of log lines and generate
    local statistics.
    */
    static Statistics processChunk(
        const std::vector<std::string>& lines);
};
#pragma once

#include <chrono>

#include "Types.h"

using hr_clock = std::chrono::high_resolution_clock;

class RAIITimer
{
public:
    RAIITimer(conststrref name = "Test");
    ~RAIITimer();

private:
    hr_clock::time_point m_start;
    hr_clock::time_point m_end;
    std::string m_name;
};


class StartStopTimer
{
public:
    StartStopTimer(conststrref name = "Test");

    void start();
    void stop();

private:
    hr_clock::time_point m_start;
    hr_clock::time_point m_end;
    std::string m_name;
    bool m_started;
};

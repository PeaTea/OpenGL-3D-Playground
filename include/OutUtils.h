#pragma once
#include <iostream>
#include <sstream>

enum class lstream
{
    info,
    warning,
    exception,
    fatal_error
};

namespace logging
{
    void log(const std::string& msg, lstream log_stream = lstream::info);
    void log_to_file(const std::string& msg, const std::string& filename, lstream log_stream = lstream::info);
}

namespace output
{
    template <typename T>
    void print(const T& msg)
    {
        std::cout << msg << "\n";
    }
}
#pragma once
#include <string>

enum class lstream
{
    info,
    warning,
    error
};

namespace logging
{
    template <typename T>
    extern void log(const T& msg, lstream log_stream);

    template <typename T>
    extern bool log_to_file(const T& msg, const std::string& filename);
}


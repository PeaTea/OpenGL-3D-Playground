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
    extern void log(const std::string& msg, lstream log_stream);
    extern void log_to_file(const std::string& msg, const std::string& filename);
}


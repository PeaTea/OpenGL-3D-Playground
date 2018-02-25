#pragma once

#include "Types.h"

#include <vector>

namespace utils
{
    std::string discard(conststrref str, conststrref exclude);
    std::vector<std::string> split(conststrref str, const char& exclude);
}

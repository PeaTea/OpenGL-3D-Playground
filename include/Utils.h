#pragma once

#include "Types.h"

#include <vector>

namespace utils
{
    std::string discard(conststrref str, conststrref exclude);
    void split(conststrref str, const char& exclude, std::vector<std::string>& parts);
}

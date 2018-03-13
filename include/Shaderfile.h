#pragma once

#include <array>

#include "Types.h"

namespace shaderfile
{
    struct Data
    {
        // Size is num of supported shaders (until now)
        std::array<std::string, 3> data = {"", "", ""};
    };

    extern Data parse(conststrref path);
}
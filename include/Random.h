#pragma once

#include <random>
#include <ctime>

namespace random
{
    template <typename T>
    int betweeni(T min, T max)
    {
        std::mt19937 random_engine {time(0)};
        std::uniform_int_distribution<T> range {min, max};

        return range(random_engine);
    }

    template <typename T>
    T betweenr(T min, T max)
    {
        std::mt19937 random_engine {time(0)};
        std::uniform_real_distribution<T> range {min, max};

        return range(random_engine);
    }
}
#pragma once

namespace maths
{
    const float PI = 3.141592653f;

    long long int_pow(long long x, int n);
    float float_pow(float x, int n);
    float sqrt(float n, float accuracy = 0.001);
    int roundf(float n);
};

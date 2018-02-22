#include "Maths.h"

#include <cmath>

namespace maths
{
    namespace
    {
        const int MOD = 1000000007;
    }

    long long int_pow(long long x, int n)
    {
        long long res = 1;
        while(n > 0)
        {
            if(n & 1)
            {
                res = (res * x) % MOD;
            }
            x = (x * x) % MOD;
            x >>= 1;
        }
        return res;
    }

    float float_pow(float x, int n)
    {
        float res = x;
        for(int i = n; i > 1; i--)
        {
            x *= x;
        }
        return res;
    }

    double sqrt(double x, double accuracy)
    {
        double guess = log(x);
        while(true)
        {
            double new_guess = (x / guess + guess) * 0.5f;
            if(std::fabs(new_guess - guess) <= accuracy)
                return guess;
            guess = new_guess;
        }
    }

    int roundf(float n)
    {
        return (int) (n + 0.5f);
    }
}
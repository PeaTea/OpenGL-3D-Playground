#include "Maths.h"

const int MOD = 1000000007;

long long Maths::int_pow(long long x, int n)
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

float Maths::float_pow(float x, int n)
{
    float res = x;
    for(int i = n; i > 1; i--)
    {
        x *= x;
    }
    return res;
}


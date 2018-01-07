#pragma once

#include <iostream>

struct Vec2
{
    Vec2()
    {
    }

    Vec2(float x)
        :   x   {x}
        ,   y   {x}
    {
    }

    Vec2(float x, float y)
        :   x   {x}
        ,   y   {y}
    {
    }

    float x, y;


public:
    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend Vec2 operator+(Vec2 left, const Vec2& right)
    {
        left += right;
        return left;
    }

    friend Vec2 operator+(Vec2 left, const float& value)
    {
        left.x += value;
        left.y += value;
        return left;
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    friend Vec2 operator-(Vec2 left, const Vec2& right)
    {
        left -= right;
        return left;
    }

    friend Vec2 operator-(Vec2 left, const float& value)
    {
        left.x -= value;
        left.y -= value;
        return left;
    }

    Vec2& operator*=(const Vec2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    friend Vec2 operator*(Vec2 left, const Vec2& right)
    {
        left *= right;
        return left;
    }

    friend Vec2 operator*(Vec2 left, const float& value)
    {
        left.x *= value;
        left.y *= value;
        return left;
    }

    Vec2& operator/=(const Vec2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    friend Vec2 operator/(Vec2 left, const Vec2& right)
    {
        left /= right;
        return left;
    }

    friend Vec2 operator/(Vec2 left, const float& value)
    {
        left.x /= value;
        left.y /= value;
        return left;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vec2& vec)
    {
        stream << vec.x << ", " << vec.y;
        return stream;
    }
};


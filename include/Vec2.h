#pragma once

#include <iostream>

template <typename T>
struct Vec2
{
    Vec2<T>()
    {
    }

    Vec2<T>(T x)
        :   x  {x}
        ,   y  {x}
    {
    }

    Vec2<T>(T x, T y)
        :   x  {x}
        ,   y  {y}
    {
    }

    T x, y;

public:
    Vec2<T>& operator+=(const Vec2<T>& other)
    {
        x = x + other.x;
        y = y + other.y;
        return *this;
    }

    friend Vec2<T> operator+(Vec2<T> left, const Vec2<T>& right)
    {
        left += right;
        return left;
    }

    friend Vec2<T> operator+(Vec2<T> left, const T& value)
    {
        left.x += value;
        left.y += value;
        return left;
    }

    Vec2<T>& operator-=(const Vec2<T>& other)
    {
        x = x - other.x;
        y = y - other.y;
        return *this;
    }
    
    friend Vec2<T> operator-(Vec2<T> left, const Vec2<T>& right)
    {
        left -= right;
        return left;
    }

    friend Vec2<T> operator-(Vec2<T> left, const T& value)
    {
        left.x -= value;
        left.y -= value;
        return left;
    }

    Vec2<T>& operator*=(const Vec2<T>& other)
    {
        x = x * other.x;
        y = y * other.y;
        return *this;
    }

    friend Vec2<T> operator*(Vec2<T> left, const Vec2<T>& right)
    {
        left *= right;
        return left;
    }

    friend Vec2<T> operator*(Vec2<T> left, const T& value)
    {
        left.x *= value;
        left.y *= value;
        return left;
    }

    Vec2<T>& operator/=(const Vec2<T>& other)
    {
        x = x / other.x;
        y = y / other.y;
        return *this;
    }

    friend Vec2<T> operator/(Vec2<T> left, const Vec2<T>& right)
    {
        left /= right;
        return left;
    }

    friend Vec2<T> operator/(Vec2<T> left, const T& value)
    {
        left.x /= value;
        left.y /= value;
        return left;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Vec2<T>& vec)
    {
        stream << vec.x << ", " << vec.y;
        return stream;
    }
};


#pragma once

#include <ostream>
#include <iostream>
#include <cmath>

template<typename T>
struct vec2
{
    T x;
    T y;

    constexpr vec2(T x, T y)
        : x(x)
        , y(y)
    {}
};

template<typename T>
struct vec3
{
    T x;
    T y;
    T z;

    constexpr vec3(T x, T y, T z)
        : x(x)
        , y(y)
        , z(z)
    {}
};

template<typename T>
constexpr vec3<T> operator *(vec3<T> const& lhs, vec3<T> const& rhs)
{
    return vec3<T>{lhs.x*rhs.x,lhs.y*rhs.y,lhs.z*rhs.z};
}

template<typename T>
struct mat3
{
    vec3<T> x;
    vec3<T> y;
    vec3<T> z;

    constexpr mat3(vec3<T> const& x, vec3<T> const& y, vec3<T> const& z)
        : x(x)
        , y(y)
        , z(z)
    {}

    constexpr mat3()
        : x({1,0,0})
        , y({0,1,0})
        , z({0,0,1})
    {}
};

template<typename T>
constexpr T radsToDegree(T rads)
{
    return rads *180.0f/M_PI;
}

template<typename T>
constexpr T degreeToRads(T degrees)
{
    return degrees * (M_PI / 180.0f);
}

template<typename T>
constexpr mat3<T> translate(mat3<T> const& m, vec2<T> const& v)
{
    auto result = m;
    result.x.z += v.x;
    result.y.z += v.y;

    return result;
}

template<typename T>
constexpr mat3<T> rotate(T degrees)
{
    return {
          { cos(degrees), -sin(degrees), 0 }
        , { sin(degrees), cos(degrees),  0 }
        , { 0,            0,             1 }
    };
}

template<typename T>
constexpr T v_length(vec2<T> const& v)
{
    float f = (v.x * v.x) + (v.y * v.y);
    return std::sqrt(f);

}

template<typename T>
constexpr vec2<T> v_normalize(vec2<T> const& v)
{
    auto const l = v_length(v);
    return { v.x/l, v.y/l };
}

template<typename T>
constexpr T dot(vec2<T> const& v1, vec2<T> const& v2)
{
    return (v1.x*v2.x)+(v1.y*v2.y);
}

template<typename T>
constexpr T perp_dot(vec2<T> const& a, vec2<T> const & b)
{
    return (a.y*b.x) - (a.x*b.y);
}

template<typename T>
constexpr vec2<T> operator *(mat3<T> const& m, vec2<T> const& v)
{
    return {   (m.x.x*v.x)+(m.x.y*v.y)+(m.x.z*1)
             , (m.y.x*v.x)+(m.y.y*v.y)+(m.y.z*1)
            };
}

template<typename T, typename S>
constexpr vec2<T> operator *(vec2<T> const& v, S scalar)
{
    return vec2<T>{v.x*scalar,v.y*scalar};
}

template<typename T, typename S>
constexpr vec3<T> operator *(vec3<T> const& v, S scalar)
{
    return vec3<T>{v.x*scalar,v.y*scalar,v.z*scalar};
}

template<typename T, typename S>
constexpr vec2<T> operator /(vec2<T> const& l, S scalar)
{
    auto v = l;
    v.x /= scalar;
    v.y /= scalar;
    return v;
}

template<typename T, typename S>
constexpr mat3<T> operator *(mat3<T> const& v, S scalar)
{
    return mat3<T>{v.x*scalar,v.y*scalar,v.z*scalar};
}

template<typename T>
constexpr void operator +=(vec2<T> & l, vec2<T> const& r)
{
    l.x += r.x;
    l.y += r.y;
}

template<typename T>
constexpr void operator -=(vec2<T> & l, vec2<T> const& r)
{
    l.x -= r.x;
    l.y -= r.y;
}

template<typename T>
constexpr vec2<T> operator +(vec2<T> const& l, vec2<T> const& r)
{
    auto v = l;
    v += r;
    return v;
}

template<typename T, typename S>
constexpr vec2<T> operator +(vec2<T> const& l, S s)
{
    auto v = l;
    v.x += s;
    v.y += s;
    return v;
}

template<typename T>
constexpr vec2<T> operator -(vec2<T> const& l, vec2<T> const& r)
{
    auto v = l;
    v -= r;
    return v;
}

template<typename T>
constexpr vec2<T> operator /(vec2<T> const& l, vec2<T> const& r)
{
    auto v = l;
    v.x /= l.x;
    v.y /= l.y;
    return v;
}

template<typename T>
std::ostream & operator <<(std::ostream & os, vec2<T> const& v)
{
    os << "x: " << v.x << " y: " << v.y << '\n';
    return os;
}

template<typename T>
std::ostream & operator <<(std::ostream & os, mat3<T> const& m)
{
    os << "|" << m.x.x << "|" << m.x.y << "|" << m.x.z << "|" << '\n'
       << "|" << m.y.x << "|" << m.y.y << "|" << m.y.z << "|" << '\n'
       << "|" << m.z.x << "|" << m.z.y << "|" << m.z.z << "|";

    return os;
}

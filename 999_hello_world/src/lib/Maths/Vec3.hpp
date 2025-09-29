#ifndef VEC3_HPP
#define VEC3_HPP

/*********************************************************************************************************************************/
#include "../Helper/_helper.hpp"
/*********************************************************************************************************************************/
namespace Maths
{


#include <cmath>
#include <algorithm>
#include <iostream>

struct Vec3
{
    double x, y, z;

    // Constructors
    constexpr Vec3() : x(0), y(0), z(0) {}
    constexpr Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    // Unary minus
    inline Vec3 operator-() const { return Vec3(-x, -y, -z); }

    // Indexing
    inline double& operator[](int i) { return *((&x) + i); }
    inline const double& operator[](int i) const { return *((&x) + i); }

    // Vector length
    inline double length() const { return std::sqrt(x * x + y * y + z * z); }

    // Squared length (for performance)
    inline double length_squared() const { return x * x + y * y + z * z; }

    // Normalize vector
    inline Vec3 normalize() const { double len = length(); return len > 0 ? (*this) / len : *this; }

    // Dot product
    inline double dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    // Cross product
    inline Vec3 cross(const Vec3& other) const { return Vec3( y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

    // Distance between two vectors
    inline double distance(const Vec3& other) const { return (*this - other).length(); }

    // Clamp components to [min, max]
    inline Vec3 clamp(double minVal = 0.0, double maxVal = 1.0) const {
        return Vec3(
            std::clamp(x, minVal, maxVal),
            std::clamp(y, minVal, maxVal),
            std::clamp(z, minVal, maxVal)
        );
    }

    // Output stream
    friend inline std::ostream& operator<<(std::ostream& os, const Vec3& v) 
    {
        return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    }

    // Arithmetic operators
    friend inline Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
    friend inline Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
    friend inline Vec3 operator*(const Vec3& a, double s) { return Vec3(a.x * s, a.y * s, a.z * s); }
    friend inline Vec3 operator*(double s, const Vec3& a) { return a * s; }

    friend inline Vec3 operator*(const double (&m)[3][3], const Vec3& v) {
        return {
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
        };
    }

    friend inline Vec3 operator/(const Vec3& a, double s) {
        if(s == 0.0) THROW_INVALID_ARGUMENT("Divide by zero error.");
        return Vec3(a.x / s, a.y / s, a.z / s);
    }

    // Compound assignment
    inline Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    inline Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    inline Vec3& operator*=(double scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    inline Vec3& operator/=(double scalar) 
    {
        if(scalar == 0.0) THROW_INVALID_ARGUMENT("Divide by zero error.");
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    static Vec3 min(const Vec3& a, const Vec3& b) 
    {
        return Vec3(
            std::min(a.x, b.x),
            std::min(a.y, b.y),
            std::min(a.z, b.z)
        );
    }

    static Vec3 max(const Vec3& a, const Vec3& b) 
    {
        return Vec3(
            std::max(a.x, b.x),
            std::max(a.y, b.y),
            std::max(a.z, b.z)
        );
    }

    void zero(){ x = 0.0; y = 0.0; z=0.0; }

};


}

#endif 

//********************************************************************
//  File:    vec4d.h
//  Date:    Sun, 22 Oct 2023: 16:46
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VEC4D_H)
#define VEC4D_H

#include <iostream>

namespace muggy::math
{
    struct vec4d
    {
        // Basic members
        // NOTE(klek): In future, maybe use a template here for a more generic structure?
        float x, y, z, w;

        // Constructors
        vec4d() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        vec4d(const float& _x, const float& _y, const float& _z, const float& _w)
         : x(_x), y(_y), z(_z), w(_w)
        {}
        vec4d(const vec4d& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

        // Member functions
        // Implements the basic math functions for 4D vectors
        vec4d& add(const vec4d& other);
        vec4d& subtract(const vec4d& other);
        vec4d& multiply(const vec4d& other);
        vec4d& divide(const vec4d& other);

        // Math operators overloaded
        // NOTE(klek): Simply calls above math functions
        friend vec4d operator+(vec4d left, const vec4d& right);
        friend vec4d operator-(vec4d left, const vec4d& right);
        friend vec4d operator*(vec4d left, const vec4d& right);
        friend vec4d operator/(vec4d left, const vec4d& right);

        vec4d& operator+=(const vec4d& other);
        vec4d& operator-=(const vec4d& other);
        vec4d& operator*=(const vec4d& other);
        vec4d& operator/=(const vec4d& other);

        bool operator==(const vec4d other) const;
        bool operator!=(const vec4d other) const;

        // Output operators, overloaded
        friend std::ostream& operator<<(std::ostream &stream, const vec4d& vector);
    };
}

#endif
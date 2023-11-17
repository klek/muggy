//********************************************************************
//  File:    vec2d.h
//  Date:    Sun, 22 Oct 2023: 15:40
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VEC2D_H)
#define VEC2D_H

#include <iostream>

namespace muggy::math
{
    struct vec2d
    {
        // Basic members
        // NOTE(klek): In future, maybe use a template here for a more generic structure?
        float x, y;

        // Constructors
        vec2d() : x(0.0f), y(0.0f) {}
        vec2d(const float& _x, const float& _y) 
         : x(_x), y(_y) 
        {}
        vec2d(const vec2d& v) : x(v.x), y(v.y) {}

        // Member functions
        // Implements the basic math functions for 2D vectors
        vec2d& add(const vec2d& other);
        vec2d& subtract(const vec2d& other);
        vec2d& multiply(const vec2d& other);
        vec2d& divide(const vec2d& other);

        // Math operators overloaded
        // NOTE(klek): Simply calls above math functions
        friend vec2d operator+(vec2d left, const vec2d& right);
        friend vec2d operator-(vec2d left, const vec2d& right);
        friend vec2d operator*(vec2d left, const vec2d& right);
        friend vec2d operator/(vec2d left, const vec2d& right);

        vec2d& operator+=(const vec2d& other);
        vec2d& operator-=(const vec2d& other);
        vec2d& operator*=(const vec2d& other);
        vec2d& operator/=(const vec2d& other);

        bool operator==(const vec2d other) const;
        bool operator!=(const vec2d other) const;

        // Output operators, overloaded
        friend std::ostream& operator<<(std::ostream &stream, const vec2d& vector);
    };
}

#endif
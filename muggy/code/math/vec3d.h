//********************************************************************
//  File:    vec3d.h
//  Date:    Sun, 22 Oct 2023: 16:28
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VEC3D_H)
#define VEC3D_H

#include <iostream>

namespace muggy::math
{
    struct vec3d
    {
        // Basic members
        // NOTE(klek): In future, maybe use a template here for a more generic structure
        float x, y, z;

        // Constructors
        vec3d() : x(0.0f), y(0.0f) {}
        vec3d(const float& _x, const float& _y, const float& _z) 
         : x(_x), y(_y), z(_z) 
        {}
        vec3d(const vec3d& v) : x(v.x), y(v.y), z(v.z) {}

        // Member functions
        // Implements the basic math functions for 3D vectors
        vec3d& add(const vec3d& other);
        vec3d& subtract(const vec3d& other);
        vec3d& multiply(const vec3d& other);
        vec3d& divide(const vec3d& other);

        // Math operators overloaded
        // NOTE(klek): Simply calls above math functions
        friend vec3d operator+(vec3d left, const vec3d& right);
        friend vec3d operator-(vec3d left, const vec3d& right);
        friend vec3d operator*(vec3d left, const vec3d& right);
        friend vec3d operator/(vec3d left, const vec3d& right);

        vec3d& operator+=(const vec3d& other);
        vec3d& operator-=(const vec3d& other);
        vec3d& operator*=(const vec3d& other);
        vec3d& operator/=(const vec3d& other);

        bool operator==(const vec3d other) const;
        bool operator!=(const vec3d other) const;

        // Output operators, overloaded
        friend std::ostream& operator<<(std::ostream &stream, const vec3d& vector);
    };
}

#endif
//********************************************************************
//  File:    vec3d.cpp
//  Date:    Fri, 17 Nov 2023: 23:48
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "vec3d.h"

namespace muggy::math
{
    vec3d& vec3d::add(const vec3d& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }
    vec3d& vec3d::subtract(const vec3d& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

        return *this;
    }
    vec3d& vec3d::multiply(const vec3d& other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;

        return *this;
    }
    vec3d& vec3d::divide(const vec3d& other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;

        return *this;
    }

    // Math operators overloaded
    // NOTE(klek): Simply calls above math functions
    vec3d operator+(vec3d left, const vec3d& right) 
    { 
        return left.add(right); 
    }

    vec3d operator-(vec3d left, const vec3d& right) 
    { 
        return left.subtract(right); 
    }

    vec3d operator*(vec3d left, const vec3d& right) 
    { 
        return left.multiply(right); 
    }

    vec3d operator/(vec3d left, const vec3d& right) 
    { 
        return left.divide(right); 
    }
    
    vec3d& vec3d::operator+=(const vec3d& other) 
    { 
        return this->add(other); 
    }
    
    vec3d& vec3d::operator-=(const vec3d& other) 
    { 
        return this->subtract(other); 
    }
    
    vec3d& vec3d::operator*=(const vec3d& other) 
    { 
        return this->multiply(other); 
    }
    
    vec3d& vec3d::operator/=(const vec3d& other) 
    { 
        return this->divide(other); 
    }

    bool vec3d::operator==(const vec3d other) const 
    { 
        return ( this->x == other.x && 
                 this->y == other.y && 
                 this->z == other.z ); 
    }

    bool vec3d::operator!=(const vec3d other) const 
    { 
        return !(*this == other); 
    }

    // Output operators, overloaded
    std::ostream& operator<<(std::ostream &stream, const vec3d& vector)
    {
        stream << "vec3d: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";

        return stream;
    }
    
} // namespace muggy::math

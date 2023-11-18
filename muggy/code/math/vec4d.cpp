//********************************************************************
//  File:    vec4d.cpp
//  Date:    Fri, 17 Nov 2023: 23:30
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "vec4d.h"

namespace muggy::math
{
    vec4d& vec4d::add( const vec4d& other )
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;

        return *this;
    }

    vec4d& vec4d::subtract(const vec4d& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;

        return *this;
    }

    vec4d& vec4d::multiply(const vec4d& other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        this->w *= other.w;

        return *this;
    }

    vec4d& vec4d::divide(const vec4d& other)
    {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        this->w /= other.w;

        return *this;
    }

    // Math operators overloaded
    // NOTE(klek): Simply calls above math functions
    vec4d operator+(vec4d left, const vec4d& right) 
    { 
        return left.add(right); 
    }

    vec4d operator-(vec4d left, const vec4d& right) 
    { 
        return left.subtract(right); 
    }

    vec4d operator*(vec4d left, const vec4d& right) 
    { 
        return left.multiply(right); 
    }

    vec4d operator/(vec4d left, const vec4d& right) 
    { 
        return left.divide(right); 
    }

    vec4d& vec4d::operator+=(const vec4d& other) 
    { 
        return this->add(other); 
    }
    
    vec4d& vec4d::operator-=(const vec4d& other) 
    { 
        return this->subtract(other); 
    }
    
    vec4d& vec4d::operator*=(const vec4d& other) 
    { 
        return this->multiply(other); 
    }

    vec4d& vec4d::operator/=(const vec4d& other) 
    { 
        return this->divide(other); 
    }

    bool vec4d::operator==(const vec4d other) const
    {
        return ( this->x == other.x && 
                this->y == other.y && 
                this->z == other.z && 
                this->w == other.w    );
    }
    bool vec4d::operator!=(const vec4d other) const 
    { 
        return !(*this == other); 
    }

    // Output operators, overloaded
    std::ostream& operator<<(std::ostream &stream, const vec4d& vector)
    {
        stream << "vec4d: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";

        return stream;
    }

} // namespace muggy::math

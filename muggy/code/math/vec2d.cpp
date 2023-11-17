//********************************************************************
//  File:    vec2d.cpp
//  Date:    Fri, 17 Nov 2023: 23:59
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "vec2d.h"

namespace muggy::math
{
    vec2d& vec2d::add(const vec2d& other) 
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }
    vec2d& vec2d::subtract(const vec2d& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }
    vec2d& vec2d::multiply(const vec2d& other)
    {
        this->x *= other.x;
        this->y *= other.y;

        return *this;
    }
    vec2d& vec2d::divide(const vec2d& other)
    {
        this->x /= other.x;
        this->y /= other.y;

        return *this;
    }

    // Math operators overloaded
    // NOTE(klek): Simply calls above math functions
    vec2d operator+(vec2d left, const vec2d& right)
    { 
        return left.add(right); 
    }

    vec2d operator-(vec2d left, const vec2d& right)
    { 
        return left.subtract(right); 
    }

    vec2d operator*(vec2d left, const vec2d& right)
    { 
        return left.multiply(right); 
    }

    vec2d operator/(vec2d left, const vec2d& right)
    { 
        return left.divide(right); 
    }
    
    vec2d& vec2d::operator+=(const vec2d& other)
    { 
        return this->add(other); 
    }

    vec2d& vec2d::operator-=(const vec2d& other)
    { 
        return this->subtract(other); 
    }

    vec2d& vec2d::operator*=(const vec2d& other)
    { 
        return this->multiply(other); 
    }

    vec2d& vec2d::operator/=(const vec2d& other)
    { 
        return this->divide(other); 
    }

    bool vec2d::operator==(const vec2d other) const 
    { 
        return ( this->x == other.x && this->y == other.y ); 
    }

    bool vec2d::operator!=(const vec2d other) const 
    { 
        return !(*this == other); 
    }
    
    // Output operators, overloaded
    std::ostream& operator<<(std::ostream &stream, const vec2d& vector)
    {
        stream << "vec2d: (" << vector.x << ", " << vector.y << ")";

        return stream;
    }

} // namespace muggy::math

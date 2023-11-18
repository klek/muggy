//********************************************************************
//  File:    maths_funcs.cpp
//  Date:    Sat, 18 Nov 2023: 00:22
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "maths_funcs.h"
#include <cmath>

namespace muggy::math
{
    //
    // Defining sine function and overloads
    //
    // TODO(klek): Consider adding own implementations for these functions
    double maths_sin(double x) 
    { 
        return sin(x); 
    }

    float maths_sin(float x) 
    { 
        return sin(x); 
    }

    long double maths_sin(long double x) 
    { 
        return sin(x); 
    }

    //
    // Defining cosine functions and overloads
    //
    // TODO(klek): Consider adding own implementations for these functions
    double maths_cos(double x)
    {
        return cos(x); 
    }

    float maths_cos(float x)
    {
        return cos(x); 
    }

    long double maths_cos(long double x)
    {
        return cos(x); 
    }

    //
    // Defining cosine functions and overloads
    //
    // TODO(klek): Consider adding own implementations for these functions
    double maths_tan(double x)
    {
        return tan(x); 
    }

    float maths_tan(float x)
    {
        return tan(x); 
    }

    long double maths_tan(long double x)
    {
        return tan(x); 
    }
    
    //
    // Defining a toRadians function
    //
    float toRadians(float degrees)
    {
        return degrees * (M_PI / 180.0f);
    }

} // namespace muggy:math

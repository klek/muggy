//********************************************************************
//  File:    vec3dTemplate.h
//  Date:    Sun, 19 Nov 2023: 02:46
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VEC_3D_TEMPLATE_H)
#define VEC_3D_TEMPLATE_H

#include <iostream>

namespace muggy::math
{
    template <typename T>
    struct vec3dTemplate
    {
        typedef T vType;
        typedef vec3dTemplate<T> vec3Type;

        // Member variables
        union 
        {
            struct{ 
                vType x, y, z; 
            };
            struct{ 
                vType r, g, b;
            };
            struct{
                vType left, top, right;
            };
        };
        
        // Constructors
        vec3dTemplate();
        vec3dTemplate( const vType& _x, 
                       const vType& _y, 
                       const vType& _z );
        vec3dTemplate( const vec3Type& _v);

        // Member functions
        // Implement basic math functions for 3D vectors
        vec3Type& add( const vec3Type& other );
        vec3Type& subtract( const vec3Type& other );
        vec3Type& multiply( const vec3Type& other );
        vec3Type& divide( const vec3Type& other );

        // Math operators overload
        // NOTE(klek): Simply calls above math functions
        template <typename Y>
        friend vec3Type operator+( vec3Type left, const vec3dTemplate<Y>& right );
        template <typename Y>
        friend vec3Type operator-( vec3Type left, const vec3dTemplate<Y>& right );
        template <typename Y>
        friend vec3Type operator*( vec3Type left, const vec3dTemplate<Y>& right );
        template <typename Y>
        friend vec3Type operator/( vec3Type left, const vec3dTemplate<Y>& right );

        vec3Type& operator+=( const vec3Type& other );
        vec3Type& operator-=( const vec3Type& other );
        vec3Type& operator*=( const vec3Type& other );
        vec3Type& operator/=( const vec3Type& other );

        bool operator==( const vec3Type other ) const;
        bool operator!=( const vec3Type other ) const;

        // Output operators, overloaded
        template <typename Y>
        friend std::ostream& operator<<( std::ostream& stream, const vec3dTemplate<Y>& v );
    };
} // namespace muggy::math

#ifndef USE_MATH_EXTERNAL
#define INCLUDE_VEC3_CPP            1
#include "vec3dTemplate.cpp"
#undef INCLUDE_VEC3_CPP
#endif

#endif
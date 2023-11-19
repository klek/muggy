//********************************************************************
//  File:    vec4dtemplate.h
//  Date:    Sun, 19 Nov 2023: 00:23
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VEC_4D_TEMPLATE_H)
#define VEC_4D_TEMPLATE_H

#include <iostream>

namespace muggy::math
{
    template <typename T>
    struct vec4dTemplate
    {
        typedef T vType;
        typedef vec4dTemplate<T> vec4Type;

        // Member variables
        union 
        {
            struct{ 
                vType x, y, z, w; 
            };
            struct{ 
                vType r, g, b, a; 
            };
            struct{
                vType left, top, right, bottom;
            };
            struct{
                vType xPos, yPos, width, height;
            };
        };
        
        // Constructors
        vec4dTemplate();
        vec4dTemplate( const vType& _x, 
                       const vType& _y, 
                       const vType& _z, 
                       const vType& _w );
        vec4dTemplate( const vec4Type& _v);

        // Member functions
        // Implement basic math functions for 4D vectors
        vec4Type& add( const vec4Type& other );
        vec4Type& subtract( const vec4Type& other );
        vec4Type& multiply( const vec4Type& other );
        vec4Type& divide( const vec4Type& other );

        // Math operators overload
        // NOTE(klek): Simply calls above math functions
        template <typename Y>
        friend vec4Type operator+( vec4Type left, const vec4dTemplate<Y>& right );
        template <typename Y>
        friend vec4Type operator-( vec4Type left, const vec4dTemplate<Y>& right );
        template <typename Y>
        friend vec4Type operator*( vec4Type left, const vec4dTemplate<Y>& right );
        template <typename Y>
        friend vec4Type operator/( vec4Type left, const vec4dTemplate<Y>& right );

        vec4Type& operator+=( const vec4Type& other );
        vec4Type& operator-=( const vec4Type& other );
        vec4Type& operator*=( const vec4Type& other );
        vec4Type& operator/=( const vec4Type& other );

        bool operator==( const vec4Type other ) const;
        bool operator!=( const vec4Type other ) const;

        // Output operators, overloaded
        template <typename Y>
        friend std::ostream& operator<<( std::ostream& stream, const vec4dTemplate<Y>& v );
    };
} // namespace muggy::math



#endif
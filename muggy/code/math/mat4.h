//********************************************************************
//  File:    mat4.h
//  Date:    Sun, 22 Oct 2023: 17:13
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(MAT4_H)
#define MAT4_H

#include <iostream>
#include <cstring>
#include "vec3d.h"
#include "vec4d.h"
#include "maths_funcs.h"

#define FOUR_BY_FOUR (4 * 4)

namespace muggy::math
{
    struct mat4
    {
        // NOTE(klek): The element array is indexed according to column-major
        // due to OpenGL. 
        // This gives the following matrix with indicies:
        // 
        //    0     4     8    12
        //    1     5     9    13
        //    2     6    10    14
        //    3     7    11    15
        //
        union {
            float elements[FOUR_BY_FOUR];
            vec4d cols[4];
            vec4d rows[4];
        };

        // Constructors
        mat4() 
        {
            for ( int i = 0; i < FOUR_BY_FOUR; i++ )
            {
                elements[i] = 0.0f;
            }
        }
        mat4(float diagonal)
        {
            for ( int i = 0; i < FOUR_BY_FOUR; i++ )
            {
                elements[i] = 0.0f;
            }

            // Set the diagonal
            elements[4 * 0 + 0] = diagonal;
            elements[4 * 1 + 1] = diagonal;
            elements[4 * 2 + 2] = diagonal;
            elements[4 * 3 + 3] = diagonal;
        }
        mat4(const mat4& v) 
        {
            for ( int i = 0; i < FOUR_BY_FOUR; i++ )
            {
                this->elements[i] = v.elements[i];
            }
        }

        // Member functions
        vec4d getColumn(int index);
        
        // Matrix multiplikation:
        // - Row x column or column x row is the way we multiply matrices
        // - Since OpenGL uses column-major as the indexing system of the matrices
        //   we will aswell.
        // - We will adress the elements in the matrix as follows
        //   4 * column + row
        //
        // - Is there a way to do this more efficient than a 3-nested loop?
        // TODO(klek): Verify that this implementation is actually correct
        mat4& multiply(const mat4& other);

        // Vector3d-Matrix4x4 multiplication
        // - X-element in vector calculates like: Vector x first Matrix-row => Sums up the product 
        //   of elements and adds the fourth column element (from matrix) into vector element X
        //   - vec3d.x * mat4.cols[0].x + vec3d.y * mat4.cols[1].x + vec3d.z * mat4.cols[2].x + mat4.cols[3].x
        // - Y-element in vector calculates like: Vector x second Matrix-row => Similar to X, but
        //   puts result into Y
        // - Z-element in vector calculates like: Vector x third Matrix-row => Similar to X, but 
        //   puts result into Z
        // - Fourth row of matrix is not used
        vec3d multiply(const vec3d& other) const;

        // Vector4d-Matrix4x4 multiplication
        // - X-element in vector calculates like: Vector x first Matrix-row => Sums up the product 
        //   of elements and adds the fourth column element (from matrix) into vector element X
        //   - vec4d.x * mat4.cols[0].x + vec4d.y * mat4.cols[1].x + vec4d.z * mat4.cols[2].x + vec4d.w * mat4.cols[3].x
        // - Y-element in vector calculates like: Vector x second Matrix-row => Similar to X, but
        //   puts result into Y
        // - Z-element in vector calculates like: Vector x third Matrix-row => Similar to X, but 
        //   puts result into Z
        // - W-element in vector calculates like: Vector x fourth Matrix-row => Similar to X, but 
        //   puts result into Z
        vec4d multiply(const vec4d& other) const;

        friend mat4 operator*(mat4 left, const mat4& right);
        mat4& operator*=(const mat4& other);
        friend vec3d operator*(const mat4& left, const vec3d& right);
        friend vec4d operator*(const mat4& left, const vec4d& right);
        
        // Calculate the identity matrix
        // The identity matrix is a matrix with all elements of its diagonal
        // set to 1
        // The matrix looks like:
        //
        //    1     0     0     0
        //    0     1     0     0
        //    0     0     1     0
        //    0     0     0     1
        //
        static mat4 identity();

        // Calculate the orthographics matrix for a given:
        // - Left field
        // - Right field
        // - Bottom field
        // - Top field
        // - Near field
        // - Far field
        // The orthographics matrix is used to decide what is actually in our "scope" or what we
        // can actually display on the screen. It should "clip" away stuff that is outside of our
        // defined planes.
        // The matrix looks like:
        //
        //    2/(R-L)  0     0       -(L+R)/(R-L)
        //    0     2/(T-B)  0       -(B+T)/(T-B)
        //    0     0     -2/(F-N)   -(F+N)/(F-N)
        //    0     0     0          1
        //
        static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);

        // Calculate the perspective matrix for a given: 
        // - Field of view
        // - Aspect ratio
        // - Near field
        // - Far field
        // The perspective matrix is used to show stuff in a perspective to were the
        // camera is. It should essentially filter out stuff we cannot see, and make
        // stuff in the distance smaller etc etc.
        // The matrix looks like:
        //
        //     1/(ar*tan(fov/2)  0    0    0
        //     0     1/(tan(fov/2)    0    0
        //     0     0     -(F+N)/(F-N)    -(2*F*N)/(F - N)
        //     0     0     -1              0
        //
        static mat4 perspective(float fov, float aspectRatio, float near, float far);

        // Calculate translation matrix for a given:
        // - Translation (vec3d)
        // The translation matrix is basically an identity matrix
        // with the last column containing the translation
        // The matrix looks like:
        //
        //    1     0     0     v.x
        //    0     1     0     v.y
        //    0     0     1     v.z
        //    0     0     0     1
        //
        static mat4 translation(const vec3d& translation);

        // Calculate the rotation matrix for a given 
        // - Axis (vec3d)
        // The rotation matrix is used to rotate stuff around an axis by the
        // specified amount of degrees
        // The matrix looks like:
        //
        // TODO(klek): Fix this doc to show actual rotation matrix
        //    1     0     0     v.x
        //    0     1     0     v.y
        //    0     0     1     v.z
        //    0     0     0     1
        //
        static mat4 rotation(float angle, const vec3d& axis);

        // Calculate the scale matrix for a given:
        // - Scale (vec3d)
        // The scale matrix is basically an identity matrix with the
        // diagonal set to the scale and finishing of with a 1
        // The matrix looks like:
        //
        //    scale.x  0        0        0
        //    0        scale.y  0        0
        //    0        0        scale.z  0
        //    0        0        0        1
        //
        static mat4 scale(const vec3d& scale);

        // Output operators, overloaded
        friend std::ostream& operator<<(std::ostream &stream, const mat4& m);
    };

}

#endif
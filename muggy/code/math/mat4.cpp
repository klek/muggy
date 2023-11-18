//********************************************************************
//  File:    mat4.cpp
//  Date:    Sat, 18 Nov 2023: 00:04
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "mat4.h"

namespace muggy::math
{
    vec4d mat4::getColumn(int index)
    {
        index *= 4;
        return ( vec4d( elements[index], 
                        elements[index + 1], 
                        elements[index + 2], 
                        elements[index + 3]) );
    }
    
    // Matrix multiplikation:
    // - Row x column or column x row is the way we multiply matrices
    // - Since OpenGL uses column-major as the indexing system of the matrices
    //   we will aswell.
    // - We will adress the elements in the matrix as follows
    //   4 * column + row
    //
    // - Is there a way to do this more efficient than a 3-nested loop?
    // TODO(klek): Verify that this implementation is actually correct
    mat4& mat4::multiply(const mat4& other) 
    {
        // Temporary storage
        float data[FOUR_BY_FOUR];

        // Iterate by row
        for ( int row = 0; row < 4; row++ )
        {
            // Iterate by column
            for ( int col = 0; col < 4; col++ )
            {
                // Sum elements here
                float sum = 0;
                for ( int e = 0; e < 4; e++ )
                {
                    // Sum row x column here
                    sum += elements[4 * e + row] * other.elements[4 * col + e];
                }
                // NOTE(klek): With current setup we will fill in index as:
                // 0->4->8->12
                // 1->5->9->13
                // 2->6->10->14
                // 3->7->11->15
                data[4 * col + row] = sum;
            }
        }
        memcpy( elements, data, ( FOUR_BY_FOUR * sizeof(float) ) );

        return *this;
    }

    // Vector3d-Matrix4x4 multiplication
    // - X-element in vector calculates like: Vector x first Matrix-row => Sums up the product 
    //   of elements and adds the fourth column element (from matrix) into vector element X
    //   - vec3d.x * mat4.cols[0].x + vec3d.y * mat4.cols[1].x + vec3d.z * mat4.cols[2].x + mat4.cols[3].x
    // - Y-element in vector calculates like: Vector x second Matrix-row => Similar to X, but
    //   puts result into Y
    // - Z-element in vector calculates like: Vector x third Matrix-row => Similar to X, but 
    //   puts result into Z
    // - Fourth row of matrix is not used
    vec3d mat4::multiply(const vec3d& other) const
    {
        return ( vec3d( cols[0].x * other.x + cols[1].x * other.y + cols[2].x * other.z + cols[3].x,
                        cols[0].y * other.x + cols[1].y * other.y + cols[2].y * other.z + cols[3].y,
                        cols[0].z * other.x + cols[1].z * other.y + cols[2].z * other.z + cols[3].z ) );
    }

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
    vec4d mat4::multiply(const vec4d& other) const
    {
        return ( vec4d( cols[0].x * other.x + cols[1].x * other.y + cols[2].x * other.z + cols[3].x * other.w,
                        cols[0].y * other.x + cols[1].y * other.y + cols[2].y * other.z + cols[3].y * other.w,
                        cols[0].z * other.x + cols[1].z * other.y + cols[2].z * other.z + cols[3].z * other.w,
                        cols[0].w * other.x + cols[1].w * other.y + cols[2].w * other.z + cols[3].w * other.w ) );

    }

    mat4 operator*(mat4 left, const mat4& right)
    { 
        return left.multiply(right); 
    }
    
    mat4& mat4::operator*=(const mat4& other)
    { 
        return this->multiply(other); 
    }

    vec3d operator*(const mat4& left, const vec3d& right)
    { 
        return left.multiply(right); 
    }

    vec4d operator*(const mat4& left, const vec4d& right)
    { 
        return left.multiply(right); 
    }
    
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
    mat4 mat4::identity() 
    { 
        return mat4(1.0f); 
    }

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
    mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        mat4 result(1.0f);

        // Setting diagonal
        result.elements[4 * 0 + 0] = 2.0f / ( right - left );
        result.elements[4 * 1 + 1] = 2.0f / ( top - bottom );
        result.elements[4 * 2 + 2] = 2.0f / ( near - far );

        // Setting last column
        result.elements[4 * 3 + 0] = ( left + right ) / ( left - right );
        result.elements[4 * 3 + 1] = ( bottom + top ) / ( bottom - top );    
        result.elements[4 * 3 + 2] = ( far + near ) / ( near - far );

        return result;
    }

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
    mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
    {
        mat4 result;

        float index5 = 1.0f / maths_tan(toRadians(0.5f * fov));
        float index0 = index5 / aspectRatio;
        float index10 = (near + far) / (near - far);
        float index14 = (2.0f * near * far) / (near - far);

        result.elements[4 * 0 + 0] = index0;
        result.elements[4 * 1 + 1] = index5;
        result.elements[4 * 2 + 2] = index10;
        result.elements[4 * 2 + 3] = -1.0f;
        result.elements[4 * 3 + 2] = index14;

        return result;
    }

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
    mat4 mat4::translation(const vec3d& translation) 
    {
        mat4 result(1.0f);

        // Set the last column
        result.elements[4 * 3 + 0] = translation.x;
        result.elements[4 * 3 + 1] = translation.y;
        result.elements[4 * 3 + 2] = translation.z;

        return result;
    }

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
    mat4 mat4::rotation(float angle, const vec3d& axis)
    {
        mat4 result(1.0f);

        float rad = toRadians(angle);
        float c = maths_cos(rad);
        float s = maths_sin(rad);
        float omc = 1.0f - c;

        result.elements[4 * 0 + 0] = axis.x * omc + c;
        result.elements[4 * 1 + 0] = axis.y * axis.x * omc + axis.z * s;
        result.elements[4 * 2 + 0] = axis.x * axis.z * omc - axis.y * s;

        result.elements[4 * 0 + 1] = axis.x * axis.y * omc - axis.z * s;
        result.elements[4 * 1 + 1] = axis.y * omc + c;
        result.elements[4 * 2 + 1] = axis.y * axis.z * omc + axis.x * s;

        result.elements[4 * 0 + 2] = axis.x * axis.z * omc + axis.y * s;
        result.elements[4 * 1 + 2] = axis.y * axis.z * omc - axis.x * s;
        result.elements[4 * 2 + 2] = axis.z * omc + c;
        
        return result;
    }

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
    mat4 mat4::scale(const vec3d& scale)
    {
        mat4 result(1.0f);

        // Set the diagonal
        result.elements[4 * 0 + 0] = scale.x;
        result.elements[4 * 1 + 1] = scale.y;
        result.elements[4 * 2 + 2] = scale.z;
        
        return result;
    }

    // Output operators, overloaded
    std::ostream& operator<<(std::ostream &stream, const mat4& m)
    {
        const int rowColSize = 4;

        stream << "Matrix: \n"; // << std::endl;
        for ( int row = 0; row < rowColSize; row++ )
        {
            stream << "       ( ";
            for ( int col = 0; col < rowColSize; col++ )
            {
                stream << m.elements[rowColSize * col + row] << ", ";
            }
            stream << ")\n";// << std::endl;
        }

        return stream;
    }

} // namespace muggy::math

//********************************************************************
//  File:    math.cpp
//  Date:    Thu, 22 Feb 2024: 11:36
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "math.h"

namespace muggy::math
{
    // NOTE(klek): This is a temporary solution to allow conversion
    //             between Euler to Quaternion
    // TODO(klek): Implement Quaternion class or similar functionality
    //             in the v4d class
    //
    // Defining Quaternion conversion functions
    //
    math::fv4d toQuaternionFromEuler( float& roll, float& pitch, float& yaw )
    {
        // NOTE(klek): This implementation was yoinked from wikipedia
        // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Source_code
        
        // Roll, pitch and yaw angles are assumed to be in radian
        math::fv4d res{};

        float cr = maths_cos( roll * 0.5f );
        float sr = maths_sin( roll * 0.5f );
        float cp = maths_cos( pitch * 0.5f );
        float sp = maths_sin( pitch * 0.5f );
        float cy = maths_cos( yaw * 0.5f );
        float sy = maths_sin( yaw * 0.5f );

        res.w = ( cr * cp * cy ) + ( sr * sp * sy );
        res.x = ( sr * cp * cy ) - ( cr * sp * sy );
        res.y = ( cr * sp * cy ) + ( sr * cp * sy );
        res.z = ( cr * cp * sy ) - ( sr * sp * cy );

        return res;
    }

    math::fv4d toQuaternionFromEuler( math::fv3d euler )
    {
        return toQuaternionFromEuler( euler.x, euler.y, euler.z );
    }

} // namespace muggy::math

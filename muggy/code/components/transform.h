//********************************************************************
//  File:    transform.h
//  Date:    Fri, 24 Nov 2023: 21:01
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(TRANSFORM_H)
#define TRANSFORM_H

#include "componentsCommon.h"

namespace muggy::transform
{
    struct init_info
    {
        // Position in x, y, z
        float position[3];
        // Rotation in x, y, z, w (Quaternion)
        float rotation[4]{ };
        // Scale in x, y, z
        float scale[3]{ 1.0f, 1.0f, 1.0f };
    };

    component createTransform( const init_info& info, 
                               game_entity::entity entity );
    void removeTransform( component c );
} // namespace muggy::transform


#endif
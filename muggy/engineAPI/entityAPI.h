//********************************************************************
//  File:    entityAPI.h
//  Date:    Thu, 22 Feb 2024: 13:29
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(ENTITY_API_H)
#define ENTITY_API_H

#include "engineCommon.h"
#include "gameEntity.h"
#include "../code/components/entity.h"
#include "../code/components/transform.h"
#include "../code/components/script.h"

#define MAX_POS_ELEMENTS    3
#define MAX_EUL_ELEMENTS    3
#define MAX_SCALE_ELEMENTS  3
#define MAX_QUAT_ELEMENTS   4

namespace muggy
{
    struct transform_component
    {
        // Position in x, y, z
        float position[MAX_POS_ELEMENTS];
        // Rotation in roll, pitch, yaw, (Euler)
        float rotation[MAX_EUL_ELEMENTS];
        // Scale in x, y, z
        float scale[MAX_SCALE_ELEMENTS];

        transform::init_info to_init_info();
    };

    struct script_component
    {
        script::detail::scriptCreator script_creator;

        script::init_info to_init_info();
    };

    // This struct is simply a list of the components
    struct game_entity_descriptor
    {
        transform_component transform;
        script_component    script;
    };

    //****************************************************************
    // Exported functions for the entity handling
    MUGGY_API
    muggy::id::id_type createGameEntity( game_entity_descriptor* e );

    MUGGY_API
    void removeGameEntity( id::id_type id );

    MUGGY_API
    script::detail::scriptCreator getScriptCreator( const char* name );
    //****************************************************************

} // namespace muggy


#endif
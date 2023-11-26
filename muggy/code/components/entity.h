//********************************************************************
//  File:    entity.h
//  Date:    Fri, 24 Nov 2023: 20:28
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(ENTITY_H)
#define ENTITY_H

#include "componentsCommon.h"

namespace muggy
{
    // ***************************************************************
    // Forward declaration of the transforms init_info
    namespace transform
    {
        struct init_info;
    } // namespace transform
    // ***************************************************************

    namespace game_entity
    {
        struct entity_info
        {
            // should contain a transform
            transform::init_info* transform{ nullptr };
        };
    
        entity createGameEntity( const entity_info& info );
        void removeGameEntity( entity e );
        bool isAlive( entity e );

    } // namespace game_entity
    
    

} // namespace muggy


#endif
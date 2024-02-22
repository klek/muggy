//********************************************************************
//  File:    script.h
//  Date:    Sun, 18 Feb 2024: 13:22
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(SCRIPT_H)
#define SCRIPT_H

#include "componentsCommon.h"

namespace muggy::script
{
    struct init_info
    {
        detail::scriptCreator scriptCreator;
    };

    component createScript( const init_info& info, 
                            game_entity::entity e );
    void removeScript( component c );

    // Update function for scripts
    void update( float dt );

} // namespace muggy::script


#endif
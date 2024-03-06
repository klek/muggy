//********************************************************************
//  File:    character.h
//  Date:    Sun, 18 Feb 2024: 16:12
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(CHARACTER_H)
#define CHARACTER_H

#include "gameEntity.h"
//#include "entityAPI.h"

namespace firstGame
{
    class character_script : public muggy::script::entity_script
    {
    public:
        constexpr explicit character_script( muggy::game_entity::entity e )
         : muggy::script::entity_script( e ) {}
        
        ~character_script( ) = default;

        void begin( ) override;
        void update( float dt ) override;
    };
} // namespace firstGame



#endif
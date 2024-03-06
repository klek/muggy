//********************************************************************
//  File:    character.cpp
//  Date:    Sun, 18 Feb 2024: 16:12
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "character.h"

#include <iostream>

namespace firstGame
{
    // Register this script with the engine
    REGISTER_SCRIPT(character_script);

    void character_script::begin( )
    {
        // Do startup setup
    }

    void character_script::update( float dt )
    {
        // Do character update

        static uint32_t i { 300 };

        if ( ( i++ % 100 ) == 0 )
        {
            std::cout << '\a' << std::endl;
            std::cout << "plop" << std::endl;
        }
    }
} // namespace firstGame


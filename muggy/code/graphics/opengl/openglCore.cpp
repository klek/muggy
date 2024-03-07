//********************************************************************
//  File:    openglCore.cpp
//  Date:    Mon, 13 Nov 2023: 01:29
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "openglCore.h"

namespace muggy::graphics::opengl::core
{
    namespace { // Anonymous namespace, ie only for use in this cpp-file

    } // Anonymous namespace, ie only for use in this cpp-file

    bool initialize( void )
    {
        // For future:
        // Determine which adapter (i.e graphics card) to use
        // Determine what the maximum feature level that is supported
        // Create a device interface (virtual adapter)

        // Today we use glew to help us with this

        return false;
    }

    void shutdown( void )
    {

    }
}
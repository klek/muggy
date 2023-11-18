//********************************************************************
//  File:    platform.h
//  Date:    Mon, 13 Nov 2023: 03:34
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(PLATFORM_H)
#define PLATFORM_H

#include "../common/common.h"
#include "window.h"

// Defining GLFW here, this should likely be done in other places
#ifndef GLFW
#define GLFW
#endif


namespace muggy::platform
{
    struct window_init_info;

    window createWindow( const window_init_info* const init_info = nullptr );
    void removeWindow( windowId id );
}


#endif
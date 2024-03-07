//********************************************************************
//  File:    graphicsPlatformInterface.h
//  Date:    Mon, 13 Nov 2023: 00:56
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(GRAPHICS_PLATFORM_INTERFACE_H)
#define GRAPHICS_PLATFORM_INTERFACE_H

#include "../common/common.h"
//#include "renderer.h"

namespace muggy::graphics
{
    struct platform_interface
    {
        bool(*initialize)(void);
        void(*shutdown)(void);
    };
}


#endif
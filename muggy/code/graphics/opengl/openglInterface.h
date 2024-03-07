//********************************************************************
//  File:    opengliInterface.h
//  Date:    Mon, 13 Nov 2023: 01:06
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(OPEN_GL_INTERFACE_H)
#define OPEN_GL_INTERFACE_H

#include "../../common/common.h"

namespace muggy::graphics 
{
    struct platform_interface;

    namespace opengl
    {
        void getPlatformInterface( platform_interface& interface );
    } // namespace opengl
    
} // namespace muggy::graphics


#endif
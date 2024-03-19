//********************************************************************
//  File:    openglInterface.cpp
//  Date:    Mon, 13 Nov 2023: 01:20
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "../../common/common.h"
#include "openglInterface.h"
#include "../graphicsPlatformInterface.h"
#include "openglCore.h"

namespace muggy::graphics::opengl 
{
    namespace // Anonymous namespace, ie only for use in this cpp-file
    {

    } // // Anonymous namespace, ie only for use in this cpp-file
    
    void getPlatformInterface( platform_interface& platformInterface )
    {
        platformInterface.initialize = core::initialize;
        platformInterface.shutdown = core::shutdown;
    }
}
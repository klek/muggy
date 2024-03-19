//********************************************************************
//  File:    d3d12Interface.cpp
//  Date:    Thu, 07 Mar 2024: 17:27
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "d3d12Interface.h"
#include "d3d12Common.h"
#include "d3d12Core.h"

namespace muggy::graphics::d3d12
{
    namespace // Anonymous namespace, ie only for use in this cpp-file
    {
        
    } // Anonymous namespace, ie only for use in this cpp-file
    
    void getPlatformInterface( platform_interface& platformInterface )
    {
        platformInterface.initialize = core::initialize;
        platformInterface.shutdown = core::shutdown;
    }
    
} // namespace muggy::graphics::d3d12

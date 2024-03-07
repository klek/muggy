//********************************************************************
//  File:    vulkanInterface.cpp
//  Date:    Thu, 07 Mar 2024: 16:55
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "vulkanInterface.h"
#include "vulkanCommon.h"
#include "vulkanCore.h"

namespace muggy::graphics::vulkan
{
    namespace // Anonymous namespace, ie only for use in this cpp-file
    {
        
    } // Anonymous namespace, ie only for use in this cpp-file
    
    void getPlatformInterface( platform_interface& interface )
    {
        interface.initialize = core::initialize;
        interface.shutdown = core::shutdown;
    }
    
} // namespace muggy::graphics::vulkan

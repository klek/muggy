//********************************************************************
//  File:    vulkanInterface.cpp
//  Date:    Thu, 07 Mar 2024: 16:55
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "vulkanCommon.h"
#include "../graphicsPlatformInterface.h"
#include "vulkanInterface.h"
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

        // TODO(klek): Add assignment of the low level surface
        //             function calls here
        interface.surface.create = core::createSurface;
        interface.surface.remove = core::removeSurface;
        interface.surface.resize = core::resizeSurface;
        interface.surface.getWidth = core::getSurfaceWidth;
        interface.surface.getHeight = core::getSurfaceHeigth;
        interface.surface.render = core::renderSurface;

        // Finally specify which platform this interface uses
        interface.platform = graphics_platform::VULKAN;
    }
    
} // namespace muggy::graphics::vulkan

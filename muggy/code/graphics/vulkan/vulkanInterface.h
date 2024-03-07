//********************************************************************
//  File:    vulkanInterface.h
//  Date:    Thu, 07 Mar 2024: 16:51
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VULKAN_INTERFACE_H)
#define VULKAN_INTERFACE_H

#include "vulkanCommon.h"

namespace muggy::graphics
{
    struct platform_interface;

    namespace vulkan
    {
        void getPlatformInterface( platform_interface& interface );
    } // namespace vulkan
    
} // namespace muggy::graphics



#endif
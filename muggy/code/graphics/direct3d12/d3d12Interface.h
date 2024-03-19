//********************************************************************
//  File:    d3d12Interface.h
//  Date:    Thu, 07 Mar 2024: 17:26
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(D3D12_INTERFACE_H)
#define D3D12_INTERFACE_H

#include "d3d12Common.h"

namespace muggy::graphics
{
    struct platform_interface;

    namespace d3d12
    {
        void getPlatformInterface( platform_interface& platformInterface );
    } // namespace vulkan
    
} // namespace muggy::graphics


#endif
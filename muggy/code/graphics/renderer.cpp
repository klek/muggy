//********************************************************************
//  File:    renderer.cpp
//  Date:    Mon, 13 Nov 2023: 00:21
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "renderer.h"
#include "graphicsPlatformInterface.h"
#include "opengl/openglInterface.h"
#include "vulkan/vulkanInterface.h"
#include "direct3d12/d3d12Interface.h"

namespace muggy::graphics 
{
    namespace // Anonymous namespace, ie only for use in this cpp-file
    {
        platform_interface gfx{};

        bool setPlatformInterface( graphics_platform platform )
        {
            switch ( platform )
            {
                case graphics_platform::OPEN_GL :
                {
                    // OpenGL support is currently not implemented
                    opengl::getPlatformInterface( gfx );
                    return true;
                    break;
                }
                case graphics_platform::DIRECT3D12 :
                {
                    // Direct3D12 support is currently not implemented
                    d3d12::getPlatformInterface( gfx );
                    return false;
                    break;
                }

                case graphics_platform::VULKAN :
                {
                    // Vulkan support is currently not implemented
                    vulkan::getPlatformInterface( gfx );
                    return false;
                    break;
                }
                
                default:
                    break;
            }
            return false;
        }

    } // Anonymous namespace, ie only for use in this cpp-file

    bool initialize( graphics_platform platform )
    {
        return setPlatformInterface( platform );
    }

    void shutdown( void )
    {
        gfx.shutdown();
    }
}
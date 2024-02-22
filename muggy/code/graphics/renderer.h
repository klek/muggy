//********************************************************************
//  File:    renderer.h
//  Date:    Mon, 13 Nov 2023: 00:13
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(RENDERER_H)
#define RENDERER_H

#include "../common/common.h"
#include "../platform/window.h"

namespace muggy::graphics
{
    class surface
    {

    };

    struct render_surface 
    {
        // Window pointer, for now just empty
        platform::window window{};
        graphics::surface surface{};
    };

    enum class graphics_platform : uint32_t
    {
        OPEN_GL     = 0,
        DIRECT3D12  = 1,
        VULKAN      = 2, // etc etc
    };

    bool initialize( graphics_platform platform );

    void shutdown( void );
}

#endif
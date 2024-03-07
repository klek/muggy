//********************************************************************
//  File:    engineAPI.cpp
//  Date:    Thu, 07 Mar 2024: 15:06
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "engineAPI.h"
#include "../code/utilities/utilities.h"
#include "../code/graphics/renderer.h"
#include "../code/platform/platform.h"
#include "../code/platform/platformTypes.h"

namespace muggy
{
    namespace 
    {
        // NOTE(klek): Should perhaps do this as a free_list?
        muggy::utils::vector<graphics::render_surface> surfaces;
    } // namespace 

    //****************************************************************
    // Exported functions for the entity handling
    MUGGY_API
    uint32_t createRenderSurface( platform::windowPtr host, 
                                            int32_t width, 
                                            int32_t heigth )
    {
        platform::window_init_info info 
        { 
            nullptr, 
            host, 
            nullptr, 
            0, 
            0, 
            width, 
            heigth 
        };
        graphics::render_surface surface { platform::createWindow( &info ), {} };
        assert( surface.window.isValid() );
        surfaces.emplace_back( surface );
        return (uint32_t)( surfaces.size() - 1 );
    }

    MUGGY_API
    void removeRenderSurface( uint32_t id )
    {
        assert( id < surfaces.size() );
        platform::removeWindow( surfaces[id].window.getId() );
    }

    MUGGY_API
    platform::windowPtr getSurfaceHandle( uint32_t id )
    {
        assert( id < surfaces.size() );
        return (platform::windowPtr)( surfaces[id].window.handle() );
    }
    //****************************************************************

} // namespace muggy

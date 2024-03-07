//********************************************************************
//  File:    engineAPI.h
//  Date:    Thu, 22 Feb 2024: 08:04
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(ENGINE_API_H)
#define ENGINE_API_H

#include "engineCommon.h"
#include "gameEntity.h"
#include "componentTransform.h"
#include "componentScript.h"

#include "../code/common/id.h"
#include "../code/platform/platformTypes.h"


namespace muggy
{
    
    //****************************************************************
    // Exported functions for the entity handling
    MUGGY_API
    uint32_t createRenderSurface( platform::windowPtr host, 
                                            int32_t width, 
                                            int32_t heigth );

    MUGGY_API
    void removeRenderSurface( uint32_t id );

    MUGGY_API
    platform::windowPtr getSurfaceHandle( uint32_t id );
    //****************************************************************

} // namespace muggy


#endif
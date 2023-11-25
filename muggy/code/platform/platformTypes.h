//********************************************************************
//  File:    platformTypes.h
//  Date:    Mon, 13 Nov 2023: 04:32
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(PLATFORM_TYPES_H)
#define PLATFORM_TYPES_H

#include "../common/common.h"
#include "platform.h"
#include "../event/event.h"

#if (defined(GLFW) || defined(GLFW3))
// Tell GLFW to not include any GL extension loader library
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
//#include "platformGLFW.h"

namespace muggy::platform
{
    struct window_init_info
    {
        evFnCallback    callback{ nullptr };
        GLFWwindow*     parent{ nullptr };
        const char*     caption{ nullptr };
        int32_t         left;
        int32_t         top;
        int32_t         width;
        int32_t         height;
    };
}
#elif defined(_WIN64)
#error "The platform specific code for Window 64-bit is not implemented"
namespace muggy::platform
{
    
}
#elif defined(UNIX)
#error "The platform specific code for Unix is not implemented"
namespace muggy::platform
{
    
}
#else
#error "This platform is not currently supported!"
#endif





#endif
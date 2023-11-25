//********************************************************************
//  File:    platform.cpp
//  Date:    Mon, 13 Nov 2023: 03:37
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "platform.h"
#include "platformTypes.h"

namespace muggy::platform
{
#if (defined(GLFW) || defined(GLFW3))

#elif defined(_WIN64)
#error "The platform specific code for Window 64-bit is not implemented"
#elif defined(UNIX)
#error "The platform specific code for Unix is not implemented"
#else
#error "This platform is not currently supported!"
#endif


}
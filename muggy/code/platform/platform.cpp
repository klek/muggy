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
    // struct window_info
    // {
    //     GLFWwindow*     windowHandle{ nullptr };
    //     const char*     caption{ nullptr };
    //     int32_t         width;
    //     int32_t         height;
    //     bool            isFullScreen{false};
    //     bool            isClosed{false};
    // };

    // namespace // Anonymous namespace, ie only for use in this cpp-file
    // {
    //     utils::vector<window_info> windows;
    //     utils::deque<uint32_t> available_slots;

    // } // Anonymous namespace, ie only for use in this cpp-file

    // uint32_t addToWindowsList(window_info info)
    // {
    //     uint32_t id{ id::invalid_id };
    //     if ( available_slots.empty() )
    //     {
    //         id = (uint32_t)windows.size();
    //         windows.emplace_back(info);
    //     }
    //     else
    //     {
    //         id = available_slots.front();
    //         available_slots.pop_front();
    //         assert( id != (uint32_t)-1 );
    //         windows[id] = info;
    //     }
    //     return id;
    // }

    // void removeFromWindowsList( uint32_t id )
    // {
    //     assert( id < windows.size() );
    //     available_slots.emplace_back(id);
    // }

    // window_info& getFromId( windowId id )
    // {
    //     assert( id < windows.size() );
    //     assert( windows[id].windowHandle );
    //     return windows[id];
    // }

    // window createWindow( const window_init_info* const init_info /* = nullptr*/)
    // {
    //     // TODO(klek): Set up the error callback
    //     // Set GLFW error callback
    //     //glfwSetErrorCallback();

    //     // Check the init info structure and set defaults if
    //     // it is missing
    //     const char* caption{ ( init_info && init_info->caption ) ? 
    //                            init_info->caption : "Muggy Engine" };
    //     const int32_t height{ ( init_info && (init_info->height > 0 ) ) ?
    //                             init_info->height : 640 };
    //     const int32_t width{ ( init_info && (init_info->width > 0 ) ) ?
    //                            init_info->width : 640 };

    //     // Call GLFW init, but only if we have no other windows
    //     if ( !glfwInit() )
    //     {
    //         // TODO(klek): Handle error here with logging
    //         // std::cout << "Failet to initialize GLFW!" << std::endl;
    //     }

    //     // Set up the window information structure
    //     window_info info;

    //     // Open a new window
    //     info.windowHandle = glfwCreateWindow(width, height, caption,
    //                                          NULL, NULL);

    //     // Check that the window got created
    //     if ( !info.windowHandle ) 
    //     {
    //         // TODO(klek): Handle this
    //         return { };
    //     }

    //     // Get the window size
    //     glfwGetWindowSize(info.windowHandle, &(info.width), &(info.height));
    //     window id { addToWindowsList(info) };
    //     return id;

    // }

    // void removeWindow( windowId id )
    // {
    //     window_info& info{ getFromId( id ) };
    //     glfwDestroyWindow( info.windowHandle );
    //     removeFromWindowsList( id );
    // }

#elif defined(_WIN64)
#error "The platform specific code for Window 64-bit is not implemented"
#elif defined(UNIX)
#error "The platform specific code for Unix is not implemented"
#else
#error "This platform is not currently supported!"
#endif


}
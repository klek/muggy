//********************************************************************
//  File:    platformGLFW.cpp
//  Date:    Mon, 13 Nov 2023: 17:21
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

//#include "platformGLFW.h"
#include "platformTypes.h"
#include "platform.h"
#include "../math/math.h"
//#include <algorithm>

#if (defined(GLFW) || defined(GLFW3))

namespace muggy::platform
{

    namespace // Anonymous namespace, ie only for use in this cpp-file
    {
        struct window_info
        {
            GLFWwindow*     windowHandle{ nullptr };
            /*GLFWmonitor*    monitor{ nullptr };*/
            windowId        id{ id::invalid_id };
            const char*     caption{ nullptr };
            math::POINT     left_top{ 0, 0 };
            math::RECT      area{ 0, 0, 640, 480 };
            math::RECT      fullScreenArea{ 0, 0, 0, 0 };
            bool            isFullScreen{ false };
            bool            isClosed{ false };
        };

        utils::vector<window_info> windows;
        utils::deque<uint32_t> available_slots;

        bool isWindowsListEmpty( void )
        {
            return ( windows.size() == available_slots.size() );
        }

        uint32_t addToWindowsList(window_info info)
        {
            uint32_t id{ uint32_invalid_id };
            if ( available_slots.empty() )
            {
                id = (uint32_t)windows.size();
                info.id = id;
                windows.emplace_back(info);
            }
            else
            {
                id = available_slots.front();
                available_slots.pop_front();
                assert( id != uint32_invalid_id );
                info.id = id;
                windows[id] = info;
            }
            return id;
        }

        void removeFromWindowsList( uint32_t id )
        {
            assert( id < windows.size() );
            available_slots.emplace_back(id);

            // Debugging, set the current slot to default
            window_info info{};
            windows[id] = info;
        }

        window_info& getFromId( windowId id )
        {
            assert( id < windows.size() );
            assert( windows[id].windowHandle );
            return windows[id];
        }

        window_info& getFromHandle( GLFWwindow* window )
        {
            //windowId id{ (id::id_type)glfwGetWindowUserPointer( window ) };
            uint32_t i = 0;
            for ( ; i < windows.size(); i++ )
            {
                window_info& currentSlot { windows[i] };
                if ( currentSlot.windowHandle == window )
                {
                    break;
                }
            }

            if ( i == windows.size() )
            {
                i = uint32_invalid_id;
            }
           
            windowId id{ i };

            return getFromId( id );
        }

        void setWindowFullScreen( windowId id, bool isFullScreen )
        {
            // Get the current info structure
            window_info& info{ getFromId( id ) };

            // Check if the stored state is different from the 
            // desired state
            if ( info.isFullScreen != isFullScreen )
            {
                info.isFullScreen = isFullScreen;

                if ( isFullScreen ) 
                {
                    // Desired state is fullscreen
                    // Store the current window dimensions
                    glfwGetWindowSize( info.windowHandle, 
                                       &(info.area.width), 
                                       &(info.area.height) );

                    // Do we care about position?
                    glfwGetWindowPos( info.windowHandle, 
                                      &(info.left_top.left), 
                                      &(info.left_top.top) );

                    // Then we need to get the monitor
                    int32_t count;
                    GLFWmonitor** monitors = glfwGetMonitors(&count);

                    // Here we currently bruteforce the desired monitor
                    // to the first aka primary monitor
                    GLFWmonitor* desMonitor = monitors[0];

                    const GLFWvidmode* mode = glfwGetVideoMode(desMonitor);

                    info.fullScreenArea.width = mode->width;
                    info.fullScreenArea.height = mode->height;

                    // Here we set the fullscreen
                    glfwSetWindowMonitor( info.windowHandle, desMonitor, 
                                          0, 0, 
                                          info.fullScreenArea.width, 
                                          info.fullScreenArea.height,
                                          mode->refreshRate );
                    
                }
                else 
                {
                    // Here we simply restore previous settings
                    // before we went to fullscreen mode
                    glfwSetWindowMonitor( info.windowHandle, NULL, 
                                          info.left_top.left, 
                                          info.left_top.top, 
                                          info.area.width, 
                                          info.area.height,
                                          0 );
                }
            }
        }

        bool isWindowFullScreen( windowId id )
        {
            window_info& info{ getFromId( id )  };
            return info.isFullScreen;            
        }

        void* getWindowHandle( windowId id )
        {
            window_info& info{ getFromId( id ) };
            return info.windowHandle;
        }

        void setWindowTitle( windowId id, const char* title )
        {
            window_info& info{ getFromId( id ) };
            glfwSetWindowTitle( info.windowHandle, title );

            // Update the structure
            info.caption = title;
        }

        math::u32v4d getWindowSize( windowId id )
        {
            window_info& info{ getFromId( id ) };
            
            math::RECT area{ info.isFullScreen ? info.fullScreenArea : info.area };
            return { (uint32_t)area.left, 
                     (uint32_t)area.top, 
                     (uint32_t)area.right, 
                     (uint32_t)area.bottom };
        }

        void resizeWindow( windowId id, uint32_t width, uint32_t height )
        {
            window_info& info{ getFromId( id ) };

            // Set new size, this should also trigger the callback
            // thus also letting us store this data
            glfwSetWindowSize( info.windowHandle, width, height );

            // If callback is not called, we need to do below stuff
            // // Verify that things went well
            // int32_t localWidth = 0;
            // int32_t localHeight = 0;
            // glfwGetWindowSize( info.windowHandle, &localWidth, &localHeight );

            // if ( localWidth != width )
            // {
            //     // Well something is wrong
            //     width = localWidth;
            // }
            // if ( localHeight != height )
            // {
            //     // Well something is wrong
            //     height = localHeight;
            // }

            // // Update the structure
            // info.width = width;
            // info.height = height;
        }

        bool isWindowClosed( windowId id )
        {
            window_info& info{ getFromId( id ) };

            return info.isClosed;            
        }

        void windowSizeCallback( GLFWwindow* window, int width, int heigth )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            // Update values
            // glfwGetWindowSize( info.windowHandle, &(info.width), &(info.height) )
            if ( info.isFullScreen )
            {
                info.fullScreenArea.width = width;
                info.fullScreenArea.height = heigth;
            }
            else 
            {
                info.area.width = width;
                info.area.height = heigth;
            }
        }

        void windowPosCallback( GLFWwindow* window, int32_t xpos, int32_t ypos )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );
            
            // Update values
            // glfwGetWindowPos( info.windowHandle, &(info.left), &(info.top) );
            info.left_top.left = xpos;
            info.left_top.top = ypos;
        }

        void windowCloseCallback( GLFWwindow* window )
        {
            // If we end up here, we should close the window
            // Currently we cannot call destroyWindow from this 
            // callback
            // But I guess we can set the flag isClosed and let
            // the application figure things out

            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            info.isClosed = true;
        }

    } // Anonymous namespace, ie only for use in this cpp-file

    window createWindow( const window_init_info* const init_info /* = nullptr*/)
    {
        // TODO(klek): Set up the error callback
        // Set GLFW error callback
        //glfwSetErrorCallback();

        // Call GLFW init, if this has been called before
        // this should instantly return true
        if ( !glfwInit() )
        {
            // TODO(klek): Handle error here with logging
            // std::cout << "Failed to initialize GLFW!" << std::endl;
            return { };
        }

        // Set up the window information structure
        window_info info;

        // Check the init info structure and set defaults if
        // it is missing
        info.left_top.left  = { ( init_info && ( init_info->left > 0 ) ) ?
                                  init_info->left : 0 };
        info.left_top.top   = { ( init_info && ( init_info->top > 0 ) ) ?
                                  init_info->top : 0 };
        info.area.width     = { ( init_info && ( init_info->width > 0 ) ) ?
                                  init_info->width : 640 };
        info.area.height    = { ( init_info && ( init_info->height > 0 ) ) ?
                                  init_info->height : 480 };
        info.caption        = { ( init_info && init_info->caption ) ? 
                                  init_info->caption : "Muggy Engine" };

        // Open a new window without any context
        glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
        glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE );
        info.windowHandle = glfwCreateWindow( info.area.width, 
                                              info.area.height, 
                                              info.caption, NULL,
                                              NULL);

        // Check that the window got created
        if ( !info.windowHandle ) 
        {
            // Well, it failed...
            // Check to see if this was our first window
            if ( isWindowsListEmpty() )
            {
                // If so, we simply terminate glfw
                glfwTerminate();
            }

            // Then we return an invalid window id
            return { };
        }

        // Setup the close callback
        glfwSetWindowCloseCallback( info.windowHandle, windowCloseCallback );

        // Set the position of the window
        glfwSetWindowPos( info.windowHandle, info.left_top.left, info.left_top.top );
        glfwSetWindowPosCallback( info.windowHandle, windowPosCallback );

        // Get the window size
        glfwSetWindowSize( info.windowHandle, info.area.width, info.area.height );
        glfwSetWindowSizeCallback(info.windowHandle, windowSizeCallback);

        // Add our new window to the list
        window id { addToWindowsList( info ) };
        // Finally add this id to the windowUserPointer
        //glfwSetWindowUserPointer(info.windowHandle, (void*)((uint64_t)(id)) );

        // Finally show window
        glfwShowWindow( info.windowHandle );

        return id;
    }

    void removeWindow( windowId id )
    {
        window_info& info{ getFromId( id ) };
        glfwDestroyWindow( info.windowHandle );
        removeFromWindowsList( id );

        // TODO(klek): Need to determine if this was the last window
        // If it was, we should also do glfwTerminate()
        if ( isWindowsListEmpty() )
        {
            glfwTerminate();
        }
    }
}

#include "includeWindowCpp.h"

#endif
//********************************************************************
//  File:    platformGLFW.cpp
//  Date:    Mon, 13 Nov 2023: 17:21
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "platformTypes.h"
#include "platform.h"
#include "../math/math.h"
#include "../event/event.h"
#include "../utilities/freelist.h"

#if (defined(GLFW) || defined(GLFW3))

namespace muggy::platform
{

    namespace // Anonymous namespace, ie only for use in this cpp-file
    {
        struct window_info
        {
            GLFWwindow*     windowHandle{ nullptr };
            evFnCallback    callback{ nullptr };
            window_id       id{ id::invalid_id };
            const char*     caption{ nullptr };
            math::POINT     left_top{ 0, 0 };
            math::RECT      area{ 0, 0, 640, 480 };
            math::RECT      fullScreenArea{ 0, 0, 0, 0 };
            bool            isFullScreen{ false };
            bool            shouldClose{ false };
            bool            isClosed{ false };
        };

        utils::free_list<window_info> windows;

        window_info& getFromId( window_id id )
        {
            assert( id < windows.capacity() );
            assert( windows[id].windowHandle );
            return windows[id];
        }

        window_id getIdFromHandle( GLFWwindow* window )
        {
            //void* idPtr = glfwGetWindowUserPointer( window ) ;
            //id::id_type test = *(window_id*)(idPtr);
            //const window_id id{ (id::id_type) test };
            uint32_t i = 0;
            for ( ; i < windows.capacity(); i++ )
            {
                window_info& currentSlot { windows[i] };
                if ( currentSlot.windowHandle == window )
                {
                    break;
                }
            }

            if ( i == windows.capacity() )
            {
                i = uint32_invalid_id;
            }
           
            const window_id id{ i };

            return id;
            // return window_id(i);
        }

        window_info& getFromHandle( GLFWwindow* window )
        {
            window_id id{ getIdFromHandle( window ) };

            return getFromId( id );
        }

        void setWindowFullScreen( window_id id, bool isFullScreen )
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

        bool isWindowFullScreen( window_id id )
        {
            window_info& info{ getFromId( id )  };
            return info.isFullScreen;            
        }

        void* getWindowHandle( window_id id )
        {
            window_info& info{ getFromId( id ) };
            return info.windowHandle;
        }

        void setWindowTitle( window_id id, const char* title )
        {
            window_info& info{ getFromId( id ) };
            glfwSetWindowTitle( info.windowHandle, title );

            // Update the structure
            info.caption = title;
        }

        math::u32v4d getWindowSize( window_id id )
        {
            window_info& info{ getFromId( id ) };
            
            math::RECT area{ info.isFullScreen ? info.fullScreenArea : info.area };
            return { (uint32_t)area.left, 
                     (uint32_t)area.top, 
                     (uint32_t)area.right, 
                     (uint32_t)area.bottom };
        }

        void resizeWindow( window_id id, uint32_t width, uint32_t height )
        {
            window_info& info{ getFromId( id ) };

            // Set new size, this should also trigger the callback
            // thus also letting us store this data
            glfwSetWindowSize( info.windowHandle, width, height );
        }

        bool isWindowClosed( window_id id )
        {
            window_info& info{ getFromId( id ) };

            return info.isClosed;            
        }

        void updateWindow( window_id id )
        {
            window_info& info{ getFromId( id) };

            // Make this context the current one
            glfwMakeContextCurrent( info.windowHandle );
            //glClear(GL_COLOR_BUFFER_BIT);
            glfwPollEvents();
            glfwSwapBuffers( info.windowHandle );
        }

        bool shouldWindowClose( window_id id )
        {
            window_info& info{ getFromId( id ) };
            return info.shouldClose;
        }

        void windowSizeCallback( GLFWwindow* window, int width, int height )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            // Update values
            // glfwGetWindowSize( info.windowHandle, &(info.width), &(info.height) )
            if ( info.isFullScreen )
            {
                info.fullScreenArea.width = width;
                info.fullScreenArea.height = height;
            }
            else 
            {
                info.area.width = width;
                info.area.height = height;
            }

            // Call the appropriate event via callback function
            event::windowResizeEvent event( getIdFromHandle( window ), width, height );
            info.callback( event );

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

            // Call the appropriate event via callback function
            event::windowMovedEvent event( getIdFromHandle( window ), info.left_top );
            info.callback( event );
        }

        void windowCloseCallback( GLFWwindow* window )
        {
            // If we end up here, we should close the window
            // Currently we cannot call destroyWindow from this 
            // callback
            // But I guess we can set the flag shouldClose and let
            // the application figure things out

            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            info.shouldClose = true;
            info.isClosed = true;
            glfwHideWindow( window );

            // Call the appropriate event via callback function
            event::windowCloseEvent event( getIdFromHandle( window ) );
            info.callback( event );
        }

        void windowKeyCallback( GLFWwindow* window, int key, int scanCode, int action, int mods )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            const window_id id{ getIdFromHandle( window ) };
            switch (action)
            {
                case GLFW_PRESS:
                {
                    event::keyPressedEvent event( id, key, 0);
                    info.callback( event );
                    break;
                }
                case GLFW_RELEASE:
                {
                    event::keyReleasedEvent event( id, key );
                    info.callback( event );
                    break;
                }
                case GLFW_REPEAT:
                {
                    event::keyPressedEvent event( id, key, 1);
                    info.callback( event );
                    break;
                }
                default:
                    break;
            }
        }

        void windowMouseCallback( GLFWwindow* window, int button, int action, int mods )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            const window_id id{ getIdFromHandle( window ) };
            switch (action)
            {
                case GLFW_PRESS:
                {
                    event::mouseButtonPressedEvent event( id, button );
                    info.callback( event );
                    break;
                }
                case GLFW_RELEASE:
                {
                    event::mouseButtonReleasedEvent event ( id, button );
                    info.callback( event );
                    break;
                }
                default:
                    break;
            }
        }

        void windowMouseScrolledCallback( GLFWwindow* window, double xOffset, double yOffset )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            const window_id id{ getIdFromHandle( window ) };
            event::mouseScrolledEvent event( id, (float)xOffset, (float)yOffset );
            info.callback( event );
        }

        void windowMousePosCallback( GLFWwindow* window, double xPos, double yPos )
        {
            // Get the id that belongs to the window
            window_info& info{ getFromHandle( window ) };
            assert( info.windowHandle == window );

            const window_id id{ getIdFromHandle( window ) };
            event::mouseMovedEvent event( id, (float)xPos, (float)yPos );
            info.callback( event );
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

        // Set up the callback
        // TODO(klek): Setup a default callback!
        info.callback = init_info->callback;

        // Open a new window without any context
        //glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
        // Open the window as invisible first
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
            //if ( isWindowsListEmpty() )
            if ( windows.empty() )
            {
                // If so, we simply terminate glfw
                glfwTerminate();
            }

            // Then we return an invalid window id
            return { };
        }

        // Make context current
        glfwMakeContextCurrent( info.windowHandle );

        // Setup the close callback
        glfwSetWindowCloseCallback( info.windowHandle, windowCloseCallback );

        // Set the position of the window
        glfwSetWindowPos( info.windowHandle, info.left_top.left, info.left_top.top );
        glfwSetWindowPosCallback( info.windowHandle, windowPosCallback );

        // Get the window size
        glfwSetWindowSize( info.windowHandle, info.area.width, info.area.height );
        glfwSetWindowSizeCallback( info.windowHandle, windowSizeCallback );

        // Set key callback
        glfwSetKeyCallback( info.windowHandle, windowKeyCallback );

        // Set mouse related callbacks
        glfwSetMouseButtonCallback( info.windowHandle, windowMouseCallback );
        glfwSetScrollCallback( info.windowHandle, windowMouseScrolledCallback );
        glfwSetCursorPosCallback( info.windowHandle, windowMousePosCallback );

        // Add our new window to the list
        //const window_id id { addToWindowsList( info ) };
        const window_id id{ windows.add( info ) };
        // Finally add this id to the windowUserPointer
        //glfwSetWindowUserPointer(info.windowHandle, (void*)(&id) );

        // Finally show window
        glfwShowWindow( info.windowHandle );

        return window{ id };
    }

    void removeWindow( window_id id )
    {
        window_info& info{ getFromId( id ) };
        glfwDestroyWindow( info.windowHandle );
        //removeFromWindowsList( id );
        windows.remove( id );

        // TODO(klek): Need to determine if this was the last window
        // If it was, we should also do glfwTerminate()
        //if ( isWindowsListEmpty() )
        if ( windows.empty() )
        {
            glfwTerminate();
        }
    }
}

#include "includeWindowCpp.h"

#endif
//********************************************************************
//  File:    engine.cpp
//  Date:    Sun, 18 Feb 2024: 10:29
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "application.h"
#include "../common/myTypes.h"
#include "../components/script.h"
#include "../platform/platformTypes.h"
#include "../platform/platform.h"
#include "../graphics/renderer.h"
#include <thread>

// NOTE(klek): Idea here is to have each of the engine functions to 
//             return an error code which corresponds to the current
//             execution of the engine, such that it is "hopefully"
//             easier to debug and control

extern muggy::application::application* muggy::application::createApplication( );

namespace 
{
    bool windowHasClosed{ false };
    muggy::application::application* app{ nullptr };
    muggy::graphics::render_surface gameWindow{};

    bool closeWindow( muggy::event::windowCloseEvent& e )
    {
        // If we get here we should close the window
        //muggy::platform::removeWindow( e.getId() );

        // Check if all windows are closed
        if ( gameWindow.window.isClosed() )
        {
            windowHasClosed = true;
        }

        // Return true to indicate we have dealt with the event
        return true;
    }

    void onEventCallback( muggy::event::event& e )
    {
        muggy::event::eventDispatcher dispatcher(e);

        dispatcher.dispatch<muggy::event::windowCloseEvent>( &closeWindow );

        std::cout << e << std::endl;
    }

} // anonymous namespace

// TODO(klek): Implement
uint32_t engineInitialize()
{
    // NOTE(klek): Concept
    //return loadGame();
    
    // If app is anything else than nullptr we should exit
    // NOTE(klek): This should never happen
    if ( app != nullptr )
    {
        // TODO(klek): Change this to regular error code
        return 4;
    }

    // Assign app
    app = muggy::application::createApplication( );
    // Check again that app did not return a nullptr
    // and also verify that the load of game data succeded
    if ( app != nullptr && app->loadGameData() )
    {
        // TODO(klek): Change this to regular error code
        return 2;
    }

    // Setup the window init structure
    muggy::platform::window_init_info info
    {
        // TODO(klek): Populate title, position and size from game info
        &onEventCallback, nullptr, "Muggy game", 900, 200, 640, 480
    };

    // Create the window
    gameWindow.window = muggy::platform::createWindow( &info );
    // Check that window creation worked
    if ( !gameWindow.window.isValid() )
    {
        // TODO(klek): Change this to regular error code
        return 3;
    }
    // NOTE(klek): Is this necessary?
    windowHasClosed = false;

    return 0;
}

// TODO(klek): Implement
uint32_t engineUpdate()
{
    // TODO(klek): We need to call an update function for all scripts
    //             We need to keep track of time
    //             We need to update outputs (sound/video etc)
    
    // Check if we are still running
    if ( windowHasClosed )
    {
        // TODO(klek): Change this to regular error code
        return 1;
    }

    // Update window
    gameWindow.window.update();

    // Update scripts
    muggy::script::update( 10.0f );
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return 0;
}

// TODO(klek): Implement
uint32_t engineShutdown()
{
    // Remove the window we created earlier
    muggy::platform::removeWindow( gameWindow.window.getId() );

    // NOTE(klek): Concept
    //return unloadGame();

    // Unload game data
    if ( app->unloadGameData() )
    {
        // TODO(klek): Change this to regular error code
        return 5;
    }
    // NOTE(klek): Should we really do this?
    delete app;

    return 0;
}
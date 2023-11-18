//********************************************************************
//  File:    testWindow.cpp
//  Date:    Thu, 16 Nov 2023: 19:04
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "testWindow.h"
#include "test.h"

// Include from engine
#include "muggy.h"

#ifdef TEST_WINDOW

#define NR_OF_WINDOWS           4

muggy::platform::window windows[NR_OF_WINDOWS];
static uint32_t iteration = 0;

bool engineTest::initialize( void )
{
    muggy::platform::window_init_info info [] 
    {
        { NULL, NULL, "Window Nr 1", 0, 0, 640, 480 },
        { NULL, NULL, "Window Nr 2", 0, 0, 480, 640 },
        { NULL, NULL, "Window Nr 3", 0, 0, 300, 200 },
        { NULL, NULL, "Window Nr 4", 0, 0, 800, 400 }
    };

    for ( uint32_t i = 0; i < NR_OF_WINDOWS; i++ )
    {
        windows[i] = muggy::platform::createWindow( &info[i] );
//        windows[i] = muggy::platform::createWindow( );
    }


    return true;
}

void engineTest::run( void ) 
{
    if ( iteration == 0 ) 
    {
        windows[0].setFullScreen( true );
    }
    else if ( iteration == 1 )
    {
        windows[0].setFullScreen( false );
    }
    else if ( iteration == 2 )
    {
        windows[0].setFullScreen( true );
    }
    else if ( iteration == 3 )
    {
        windows[0].setFullScreen( true );
    }
    else {
        iteration = 0;
    }
    iteration++;
    glfwPollEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}

void engineTest::shutdown( void ) 
{
    for ( uint32_t i = 0; i < NR_OF_WINDOWS; i++ )
    {
        muggy::platform::removeWindow( windows[i].getId() );
    }
}

#endif
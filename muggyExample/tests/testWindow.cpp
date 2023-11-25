//********************************************************************
//  File:    testWindow.cpp
//  Date:    Thu, 16 Nov 2023: 19:04
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "test.h"
#if TEST_WINDOW
#include "testWindow.h"

//#if TEST_WINDOW

#define NR_OF_WINDOWS           4

#define BIND_FN(x)              std::bind(&x, this, std::placeholders::_1)

muggy::platform::window         windows[NR_OF_WINDOWS];
static uint32_t iteration = 0;

bool engineTest::closeWindow( muggy::event::windowCloseEvent& e )
{
    // If we get here we should close the window
    //muggy::platform::removeWindow( e.getId() );

    uint32_t count = 0;
    // Check if all windows are closed
    for ( int i = 0; i < NR_OF_WINDOWS; i++ )
    {
        if ( windows[i].isClosed() )
        {
            count++;
        }
    }

    if ( count == NR_OF_WINDOWS )
    {
        m_IsRunning = false;
    }

    // Return true to indicate we have dealt with the event
    return true;
}

void engineTest::onEventCallback( muggy::event::event& e )
{
    muggy::event::eventDispatcher dispatcher(e);

    dispatcher.dispatch<muggy::event::windowCloseEvent>(BIND_FN(engineTest::closeWindow));

    std::cout << e << std::endl;
}


bool engineTest::initialize( void )
{
    muggy::platform::window_init_info info [] 
    {
        { BIND_FN(engineTest::onEventCallback), NULL, "Window Nr 1", 0, 0, 640, 480 },
        { BIND_FN(engineTest::onEventCallback), NULL, "Window Nr 2", 100, 100, 480, 640 },
        { BIND_FN(engineTest::onEventCallback), NULL, "Window Nr 3", 200, 200, 300, 200 },
        { BIND_FN(engineTest::onEventCallback), NULL, "Window Nr 4", 300, 300, 800, 400 }
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
    // if ( iteration % 200 ) 
    // {
    //     windows[0].setFullScreen( true );
    // }
    // else if ( iteration % 300 )
    // {
    //     windows[0].setFullScreen( false );
    // }
    
    // if ( iteration < uint32_invalid_id )
    // {
    //     iteration++;
    // }
    // else {
    //     iteration = 0;
    // }

    while ( m_IsRunning ) 
    {
        bool allClosed = false;
        for ( uint32_t i = 0; i < NR_OF_WINDOWS; i++ )
        {
            if ( !( windows[i].isClosed() ) )
            {
               windows[i].update();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void engineTest::shutdown( void ) 
{
    for ( uint32_t i = 0; i < NR_OF_WINDOWS; i++ )
    {
        muggy::platform::removeWindow( windows[i].getId() );
    }
}

#endif
//********************************************************************
//  File:    entrypoint.cpp
//  Date:    Sun, 18 Feb 2024: 10:11
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "../common/myTypes.h"
#include <iostream>

// Declare external functions for engine usage
extern uint32_t engineInitialize();
extern uint32_t engineUpdate();
extern uint32_t engineShutdown();

#if ( defined(UNIX) || defined(GLFW) || defined(GLFW3) )

// NOTE(klek): Currently not using input variables
int main( int argc , char* argv[] ) 
{

    std::cout << "Muggy engine output: " << "Started on linux" << std::endl;
    if ( engineInitialize() == 0 ) {
        bool isRunning { true };
        uint32_t retVal { 0 };
        while ( isRunning )
        {
            // NOTE(klek): Need a way to get information regarding
            //             if the loop should exit
            retVal = engineUpdate();
            if ( retVal != 0 )
            {
                isRunning = false;
            }
        }
    }

    // Turn of engine
    engineShutdown();
    return 0;
}

#elif defined(_WIN64)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

// NOTE(klek): Currently not using input variables
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
#if _DEBUG
    // In MSVC this should give us information about memory leaks
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    std::cout << "Muggy engine output: " << "Started on Windows" << std::endl;

    if ( engineInitialize() != 0 )
    {
        MSG msg;
        bool isRunning { true };
        uint32_t retVal { 0 };
        while ( isRunning )
        {
            // Get all messages from message queue
            while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );

                // Should we quit?
                isRunning &= ( msg.message != WM_QUIT );
            }

            retVal = engineUpdate();
            // NOTE(klek): Do we care about the quit message here?
            if ( retVal != 0 && isRunning == false )
            {
                isRunning = false;
            }
        }

    }

    // Turn off engine
    engineShutdown();
    return 0;
}

#else
#warning "This platform is not supported!"
#endif
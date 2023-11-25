//********************************************************************
//  File:    testWindow.h
//  Date:    Thu, 16 Nov 2023: 19:02
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(TEST_WINDOW_H)
#define TEST_WINDOW_H

#include "test.h"
//#include "muggy.h"
#include "../../muggy/code/event/event.h"
#include "../../muggy/code/platform/platform.h"
#include "../../muggy/code/platform/window.h"
#include "../../muggy/code/platform/platformTypes.h"

class engineTest : public test
{
public:
    bool initialize( void ) override;
    void run ( void ) override;
    void shutdown( void ) override;

    // Additional functions for this test
    bool closeWindow( muggy::event::windowCloseEvent& e );
    void onEventCallback( muggy::event::event& e);

private:
    bool m_IsRunning = true;
};

#endif
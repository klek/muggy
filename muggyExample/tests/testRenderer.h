//********************************************************************
//  File:    testRenderer.h
//  Date:    Thu, 07 Mar 2024: 16:22
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(TEST_RENDERER_H)
#define TEST_RENDERER_H

#include "test.h"

#include "../../muggy/code/event/event.h"
#include "../../muggy/code/platform/platform.h"
#include "../../muggy/code/platform/window.h"
#include "../../muggy/code/platform/platformTypes.h"
#include "../../muggy/code/graphics/renderer.h"

class engineTest : public test
{
public:
    bool initialize( void ) override;
    void run( void ) override;
    void shutdown( void ) override;

private:
    // Any internal variables?
};

#endif
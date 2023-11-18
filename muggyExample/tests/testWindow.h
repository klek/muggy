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

class engineTest : public test
{
public:
    bool initialize( void ) override;
    void run ( void ) override;
    void shutdown( void ) override;
};

#endif
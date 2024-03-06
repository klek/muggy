//********************************************************************
//  File:    testFreelist.cpp
//  Date:    Sat, 03 Feb 2024: 05:06
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "test.h"
#if TEST_FREELIST
#include "testFreelist.h"


bool engineTest::initialize( void )
{
    // Initialize does really nothing except to print start to cout
    std::cout << "This is start of test" << std::endl;
}

void engineTest::run( void )
{
    bool shouldQuit = false;
    char charInput = 'k';
    while ( !shouldQuit ) 
    {
        // Add elements
        m_Storage.add();
        
        
        std::cout << "Press any key, Q or q means quit: ";
        std::cin >> charInput;
        std::cout << std::endl;

        if ( charInput == 'Q' || charInput == 'q' )
        {
            shouldQuit = true;
        }
    }
}

void engineTest::shutdown( void )
{

}

#endif
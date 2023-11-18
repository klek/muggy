//********************************************************************
//  File:    main.cpp
//  Date:    Mon, 06 Nov 2023: 18:43
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "muggy.h"
#include <iostream>

#include "tests/test.h"

#if TEST_WINDOW
#include "tests/testWindow.h"
#endif



int main( int argc , char* argv[] ) 
{
    std::cout << "Hello, from muggyExample!\n";

//    muggy::print("Hello from Engine!\n");

    engineTest test;

    if ( test.initialize() ) {
        bool isRunning = true;
        uint16_t i = 0;
        while ( isRunning )
        {
            // We need to determine if any windows has closed yet
            //while ( )
            if ( !( i++ < ( uint16_invalid_id / 4 ) ) )
                isRunning = false;
            test.run();
        }
    }

    test.shutdown();

    std::cout << "Finished testing!" << std::endl;
    return 0;
}

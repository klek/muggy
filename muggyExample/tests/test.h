//********************************************************************
//  File:    test.h
//  Date:    Thu, 16 Nov 2023: 05:23
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(TEST_H)
#define TEST_H

#include <thread>

// Defines for test to run
#define TEST_ENTITIES           0
#define TEST_WINDOW             1

class test
{
public:
    virtual bool initialize() = 0;
    virtual void run() = 0;
    virtual void shutdown() = 0;
};



#endif
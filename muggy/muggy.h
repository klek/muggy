//********************************************************************
//  File:    muggy.h
//  Date:    Mon, 06 Nov 2023: 17:50
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(MUGGY_H)
#define MUGGY_H

// Include common headers, these might be removed later
#include "code/common/common.h"

// Include platform part
#include "code/platform/window.h"
#include "code/platform/platform.h"
#include "code/platform/platformTypes.h"


#include <iostream>

namespace muggy 
{
    void print( const char* msg);
}

#endif
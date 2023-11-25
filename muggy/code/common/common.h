//********************************************************************
//  File:    common.h
//  Date:    Mon, 13 Nov 2023: 00:20
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(COMMON_H)
#define COMMON_H

//#pragma warning(disables 4530) // Disable exception warning

// Defining global macros
#ifdef DEBUG_BUILD
#define DEBUG_OP(x)         x
#else
#define DEBUG_OP(x)         
#endif

#define BIT(x)              (1 << x)


// Common includes for the the engine
// C/C++ 
#include <stdint.h>
#include <assert.h>
#include <typeinfo>
#include <memory>
#include <unordered_map>
#include <iostream>

// Internal common headers
#include "../utilities/utilities.h"
#include "myTypes.h"
#include "id.h"

// Including math library
#include "../math/math.h"


#endif
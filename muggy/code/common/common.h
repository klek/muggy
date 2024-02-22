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
#define DEBUG_OP(x)             x
#else
#define DEBUG_OP(x)         
#endif

#define BIT(x)                  (1 << x)

// Count of macro
// #if ( defined(MSVC) )
// #define COUNT_OF(arr)           _countof(arr)
// #elif ( defined(GCC) )
// #define BUILD_BUG_ON_ZERO(e)    ( sizeof( struct { int:-!!(e); } ) )
// #define MUST_BE_ARRAY(arr)      BUILD_BUG_ON_ZERO( __builtin_types_compatible_p( typeof(a), typeof( &a[0] ) ) )
// #define COUNT_OF(arr)           ( sizeof(arr) / sizeof((arr)[0]) + MUST_BE_ARRAY(arr) )
// #endif


// Common includes for the the engine
// C/C++ 
#include <cstdint>
#include <assert.h>
#include <cstring>
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
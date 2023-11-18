//********************************************************************
//  File:    common.h
//  Date:    Mon, 13 Nov 2023: 00:20
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(COMMON_H)
#define COMMON_H

// Common includes for the the engine
// C/C++ 
#include <stdint.h>
#include <assert.h>
#include <typeinfo>
#include <memory>
#include <unordered_map>

// Set internal macros
#ifdef Debug
#define DEBUG_BUILD
#else
#undef _DEBUG
#endif

// Internal common headers
#include "id.h"
#include "myTypes.h"
#include "../utilities/utilities.h"

#ifdef DEBUG_BUILD
#define DEBUG_OP(x)         x
#else
#define DEBUG_OP(x)         (void(0))
#endif


#endif
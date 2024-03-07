//********************************************************************
//  File:    common.h
//  Date:    Thu, 22 Feb 2024: 13:27
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(ENGINE_COMMON_H)
#define ENGINE_COMMON_H

#if ( defined(BUILD_SHARED_LIBS) && BUILD_SHARED_LIBS==ON)
#if defined(_WIN64)
#if !defined(MUGGY_API)
#define MUGGY_API   extern "C" __declspec(dllexport)
#endif
#else
#if !defined(MUGGY_API)
#define MUGGY_API   extern "C" __attribute__((visibility("default")))
#endif
#endif
#else
#define MUGGY_API
#endif

#endif
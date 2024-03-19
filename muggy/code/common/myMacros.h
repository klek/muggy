//********************************************************************
//  File:    myMacros.h
//  Date:    Thu, 14 Mar 2024: 21:26
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(MY_MACROS_H)
#define MY_MACROS_H

// Defining global macros for debugging purposes
#if defined( DEBUG_BUILD )
#define DEBUG_OP(x)             x
#define MSG(x)                  std::cout << x << std::endl;
#else
#define DEBUG_OP(x)             
#define MSG(x)                  
#endif

#define BIT(x)                  (1 << x)

// Max and min macros
#define MUGGY_MAX(a,b)          ( ( a > b ) ? a : b )
#define MUGGY_MIN(a,b)          ( ( a < b ) ? a : b )

// Class macros
#if !defined ( MUGGY_DISABLE_COPY )
#define MUGGY_DISABLE_COPY(T)                                       \
                                explicit T( const T& ) = delete;    \
                                T& operator=(const T&) = delete;
#endif

#if !defined ( MUGGY_DISABLE_MOVE )
#define MUGGY_DISABLE_MOVE(T)                                       \
                                explicit T( T&& ) = delete;         \
                                T& operator=( T&&) = delete;
#endif

#if !defined ( MUGGY_DISABLE_COPY_AND_MOVE )
#define MUGGY_DISABLE_COPY_AND_MOVE(T)                              \
                                MUGGY_DISABLE_COPY(T)               \
                                MUGGY_DISABLE_MOVE(T)
#endif


#endif
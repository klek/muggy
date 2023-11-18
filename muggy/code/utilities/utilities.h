//********************************************************************
//  File:    utilities.h
//  Date:    Mon, 13 Nov 2023: 05:32
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(UTILITIES_H)
#define UTILITIES_H

#define USE_STL_VECTOR      1
#define USE_STL_DEQUE       1

#if USE_STL_VECTOR
#include <vector>
namespace muggy::utils
{
    template <typename T>
    using vector = std::vector<T>;
}
#else
namespace muggy::utils
{

}
#endif

#if USE_STL_DEQUE
#include <deque>
namespace muggy::utils
{
    template <typename T>
    using deque = std::deque<T>;
}
#else
namespace muggy::utils
{

}
#endif

#endif
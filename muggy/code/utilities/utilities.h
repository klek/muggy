//********************************************************************
//  File:    utilities.h
//  Date:    Mon, 13 Nov 2023: 05:32
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(UTILITIES_H)
#define UTILITIES_H

#define USE_STL_VECTOR      0
#define USE_STL_DEQUE       1

#if USE_STL_VECTOR
#include <vector>
namespace muggy::utils
{
    template <typename T>
    using vector = std::vector<T>;

    template <typename T>
    void erase_unordered( T& v, size_t index )
    {
        if ( v.size() > 1 )
        {
            // Swap item to erase with the last item
            std::iter_swap( v.begin() + index, v.end() - 1 );
            v.pop_back();
        }
        else
        {
            v.clear();
        }
    }
}
#else
#include "vector.h"
namespace muggy::utils
{
    template <typename T>
    void erase_unordered( T& v, size_t index )
    {
        v.erase_unordered( index );
    }
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

// Implement and include our own containers
#include "freelist.h"

#if !defined( _WIN64 )
// Create a template function for _countof, which is already 
// implemented in windows/vs
template < typename T, size_t N >
size_t constexpr _countof( T( &arr )[ N ] )
{
    return std::extent< T[ N ] >::value;
}
#endif

#endif
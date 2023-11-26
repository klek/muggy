//********************************************************************
//  File:    freelist.h
//  Date:    Thu, 23 Nov 2023: 19:27
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(FREELIST_H)
#define FREELIST_H

#include "../common/common.h"
#include <cstring>

namespace muggy::utils
{

#if USE_STL_VECTOR
#pragma message("WARNING: Using utils::free_list with std::vector results in duplicate calls to class destructor")
#endif

    template < typename T>
    class free_list
    {
        static_assert( sizeof(T) >= sizeof( uint32_t ));

    public:
        free_list() = default;

        explicit free_list( uint32_t count )
        {
            m_Array.reserve( count );
        }

        ~free_list()
        {
            assert(!m_Size);
#if USE_STL_VECTOR
            memset( m_Array.data(), 0, m_Array.size() * sizeof(T) );
#endif
        }

        template < class... params>
        constexpr uint32_t add( params&&... p )
        {
            uint32_t id{ uint32_invalid_id };
            // Are there any free slots?
            if ( m_NextFreeIndex == uint32_invalid_id )
            {
                // No, need to add more slots to the array
                id = (uint32_t)m_Array.size();
                m_Array.emplace_back( std::forward<params>( p )...);
            }
            else
            {
                // Yes, reuse a free slot
                id = m_NextFreeIndex;
                // Check if the this slot was already removed
                assert( ( id < m_Array.size() ) && alreadyRemoved(id) );
                m_NextFreeIndex = *(const uint32_t *const)std::addressof( m_Array[id] );
                new ( std::addressof( m_Array[id] ) ) T(std::forward<params>( p )...);
            }
            m_Size++;
            
            return id;
        }

        constexpr void remove( uint32_t id )
        {
            // Check if the this slot was already removed
            assert( ( id < m_Array.size() ) && !alreadyRemoved(id) );
            // Get a reference to the item at slot id
            T& item{ m_Array[id] };
            // Call that items destructor
            item.~T();
            // Debug only, sets the entire slot to 0xCC for debugging purposes
            DEBUG_OP( memset( std::addressof( m_Array[id] ), 0xCC, sizeof(T) ) );
            // Save the next free slot in the first four bytes of this location
            *(uint32_t *const)std::addressof( m_Array[id] ) = m_NextFreeIndex;
            // Update the next free index to point to id
            m_NextFreeIndex = id;
            m_Size--;
        }

        constexpr uint32_t size() const
        {
            return m_Size;
        }

        constexpr uint32_t capacity() const
        {
            return m_Array.size();
        }

        constexpr bool empty() const
        {
            return ( m_Array.size() == 0 );
        }

        [[nodiscard]] constexpr T& operator[]( uint32_t id )
        {
            // Check if the this slot was already removed
            assert( ( id < m_Array.size() ) && !alreadyRemoved(id) );

            return m_Array[id];
        }

        [[nodiscard]] constexpr const T& operator[]( uint32_t id ) const
        {
            // Check if the this slot was already removed
            assert( ( id < m_Array.size() ) && !alreadyRemoved(id) );

            return m_Array[id];
        }

    private:
        // For debugging with asserts
        constexpr bool alreadyRemoved( uint32_t id )
        {
            if constexpr ( sizeof(T) > sizeof( uint32_t ) )
            {
                // Skip the first 4 bytes, by setting our iterator
                // to the size of uint32_t
                uint32_t i{ sizeof( uint32_t ) };
                const uint8_t *const p{ (const uint8_t *const)std::addressof( m_Array[id] ) };
                for ( ; ( i < sizeof(T) ) && ( p[i] == 0xCC ) ; i++)
                {}
                
                // Return true if i is now equal to sizeof(T)
                return ( i == sizeof(T) );
            }
            else 
            {
                // Always return true if the T is equal to uint32_t
                return true;
            }
        }
#if USE_STL_VECTOR
        utils::vector<T>        m_Array;
#else
        utils::vector<T, false> m_Array;
#endif
        uint32_t                m_NextFreeIndex{ uint32_invalid_id };
        uint32_t                m_Size{ 0 };
    };
} // namespace muggy::utils



#endif
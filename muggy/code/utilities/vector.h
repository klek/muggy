//********************************************************************
//  File:    vector.h
//  Date:    Sun, 26 Nov 2023: 03:11
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(VECTOR_H)
#define VECTOR_H

#include "../common/common.h"

namespace muggy::utils
{
    template <typename T, bool destruct=true>
    class vector
    {
    public:
        // Constructors
        // Default contstructor, doesn't allocate memory
        vector() = default;

        // Constructor resizes the vector and initializes "count" items
        constexpr vector( uint64_t count )
        {
            resize( count );
        }

        // Constructor resize the vector and initializes "count" items 
        // using value
        constexpr vector( uint64_t count, const T& value )
        {
            resize( count, value );
        }

        template <typename it>//, typename = std::enable_if_t<std::_Is_iterator_v<it>>>
        constexpr explicit vector( it first, it last )
        {
            for ( ; first != last ; ++first )
            {
                emplace_back(*first);
            }
        }

        // Copy-constructor, constructs by copying another vector
        // The items in the copied vector must be copyable!
        constexpr vector( const vector& other )
        {
            *this = other;
        }

        // Move-constructor, constructs by moving another vector
        // The original vector will be empty after the move
        constexpr vector( const vector&& other )
         : 
            m_Capacity( other.m_Capacity ),
            m_Size( other.m_Size ),
            m_Data( other.m_Data )
        {
            other.reset();
        }

        // Copy-assignment operator, clears this vector and copies
        // items from another vector. The items must be copyable!
        constexpr vector& operator=( const vector& other )
        {
            // Check for assignment to itself, which might not be 
            // what we want!
            assert( this != std::addressof( other ) );
            if( this != std::addressof( other ) )
            {
                clear();
                reserve( other.m_Size );
                for ( auto& item : other )
                {
                    emplace_back( item );
                }
                assert( m_Size == other.m_Size );
            }
            
            return *this;
        }

        // Move-assignment operator, frees all resources in this vector
        // and moves the other vector into this one
        constexpr vector& operator=( const vector&& other )
        {
            // Check for assignment to itself, which might not be 
            // what we want!
            assert( this != std::addressof( other ) );
            if( this != std::addressof( other ) )
            {
                destroy();
                move( other );
            }
            
            return *this;
        }

        // Destructs the vector and its items as specified in the
        // template argument
        ~vector()
        {
            destroy();
        }

        // Inserts an item at the end of the vector by copying 
        // 'value'
        constexpr void push_back( const T& value )
        {
            emplace_back( value );
        }

        // Inserts an item at the end of the vector by moving 
        // 'value'
        constexpr void push_back( T&& value )
        {
            emplace_back( std::move( value ) );
        }

        // Copy- or move-constructs an item at the end of the vector
        template <typename... params>
        constexpr decltype( auto ) emplace_back( params&&... p )
        {
            if ( m_Size == m_Capacity )
            {
                // Reserve 50 % more to minimize the number of
                // reallocations
                reserve( ( ( m_Capacity + 1 ) * 3 ) >> 1 );
            }
            assert( m_Size < m_Capacity );

            T *const item { new ( std::addressof( m_Data[ m_Size ] ) ) T( std::forward<params>( p )... ) };
            m_Size++;
            return *item;
        }

        // Resizes the vector and initializes new items with their
        // default value
        constexpr void resize( uint64_t newSize )
        {
            static_assert( std::is_default_constructible_v<T>,
                           "Type must be default-constructible");
            
            // Do we need to reserve more memory?
            if ( newSize > m_Size )
            {
                // Yes, more memory needed
                reserve( newSize );
                while ( m_Size < newSize )
                {
                    emplace_back();
                }
            }
            else if ( newSize < m_Size )
            {
                // No, we need to free memory
                if constexpr ( destruct )
                {
                    destruct_range( newSize, m_Size );
                }
                m_Size = newSize;
            }

            // Do nothing if newSize == m_Size
            assert( newSize == m_Size );
        }

        constexpr void resize( uint64_t newSize, T* value )
        {
            static_assert( std::is_copy_constructible_v<T>,
                           "Type must be copy-constructible");
            
            // Do we need to reserve more memory?
            if ( newSize > m_Size )
            {
                // Yes, more memory needed
                reserve( newSize );
                while ( m_Size < newSize )
                {
                    emplace_back( value );
                }
            }
            else if ( newSize < m_Size )
            {
                // No, we need to free memory
                if constexpr ( destruct )
                {
                    destruct_range( newSize, m_Size );
                }
                m_Size = newSize;
            }

            // Do nothing if newSize == m_Size
            assert( newSize == m_Size );
        }

        // Allocates memory to contain the specified number of items
        constexpr void reserve( uint64_t newCapacity )
        {
            if ( newCapacity > m_Capacity )
            {
                // NOTE(klek): realloc() will automatically copy the
                //             data in the buffer if a new region of 
                //             memory is allocated
                void* newBuffer{ realloc( m_Data, newCapacity * sizeof(T) ) };
                assert( newBuffer );
                if( newBuffer )
                {
                    m_Data = static_cast<T*>( newBuffer );
                    m_Capacity = newCapacity;
                }
            }
        }

        // Removes the item at the specified index
        constexpr T *const erase( uint64_t index )
        {
            assert( m_Data && index < m_Size );
            return erase( std::addressof( m_Data[ index ] ) );
        }

        // Removes the item at the specified location
        constexpr T *const erase( T *const item )
        {
            assert( m_Data && 
                    item >= std::addressof( m_Data[ 0 ] ) && 
                    item < std::addressof( m_Data[ m_Size ] ) );

            if constexpr ( destruct )
            {
                item->~T();
            }
            m_Size--;
            if ( item < std::addressof( m_Data[ m_Size ] ) )
            {
                memcpy( item, 
                        ( item + 1 ), 
                        ( std::addressof( m_Data[ m_Size ] ) - item ) * sizeof( T ) );
            }

            return item;
        }

        // Same as erase() but faster because it just copies the last item
        // This means that this function does NOT preserve the order
        constexpr T *const erase_unordered( uint64_t index )
        {
            assert( m_Data && index < m_Size );
            return erase_unordered( std::addressof( m_Data[ index ] ) );
        }

        // Same as erase() but faster because it just copies the last location
        // This means that this function does NOT preserve the order
        constexpr T *const erase_unordered( T *const item )
        {
            assert( m_Data && 
                    item >= std::addressof( m_Data[ 0 ] ) && 
                    item < std::addressof( m_Data[ m_Size ] ) );

            if constexpr ( destruct )
            {
                item->~T();
            }
            m_Size--;
            if ( item < std::addressof( m_Data[ m_Size ] ) )
            {
                memcpy( item, 
                        std::addressof( m_Data[ m_Size ] ),
                        sizeof( T ) );
            }

            return item;
        }

        // Clears the vector and destructs items as specified in 
        // template argument
        constexpr void clear()
        {
            if constexpr ( destruct )
            {
                destruct_range( 0, m_Size );
            }
            m_Size = 0;
        }

        // Swaps two vectors
        constexpr void swap( vector& other )
        {
            if ( this != std::addressof( other ) )
            {
                auto temp( std::move( other ) );
                other.move( *this );
                move( temp );
            }
        }

        // Pointer to the start of data. This might be null
        [[nodiscard]] constexpr T* data()
        {
            return m_Data;
        }

        // Pointer to the start of data. This might be null
        [[nodiscard]] constexpr T *const data() const
        {
            return m_Data;
        }

        // Returns true if the vector is empty
        [[nodiscard]] constexpr bool empty() const
        {
            return m_Size == 0;
        }

        // Returns the number of elements in the vector
        [[nodiscard]] constexpr uint64_t size() const
        {
            return m_Size;
        }

        // Returns the total capacity/size of the vector
        [[nodiscard]] constexpr uint64_t capacity() const
        {
            return m_Capacity;
        }

        // Indexing operator. Returns a reference to the item at
        // the specified index
        [[nodiscard]] constexpr T& operator[]( uint64_t index )
        {
            assert( m_Data && index < m_Size );
            return m_Data[ index ];
        }

        // Indexing operator. Returns a constant reference to the 
        // item at the specified index
        [[nodiscard]] constexpr const T& operator[]( uint64_t index ) const
        {
            assert( m_Data && index < m_Size );
            return m_Data[ index ];
        }

        // Returns a reference to the item at the front of the 
        // vector. Will fault the application if used when the
        // vector is empty
        [[nodiscard]] constexpr T& front()
        {
            assert( m_Data && m_Size );
            return m_Data[ 0 ];
        }

        // Returns a const reference to the item at the front of the 
        // vector. Will fault the application if used when the
        // vector is empty
        [[nodiscard]] constexpr const T& front() const
        {
            assert( m_Data && m_Size );
            return m_Data[ 0 ];
        }

        // Returns a reference to the item at the back of the 
        // vector. Will fault the application if used when the
        // vector is empty
        [[nodiscard]] constexpr T& back()
        {
            assert( m_Data && m_Size );
            return m_Data[ m_Size - 1 ];
        }

        // Returns a const reference to the item at the back of the 
        // vector. Will fault the application if used when the
        // vector is empty
        [[nodiscard]] constexpr const T& back() const
        {
            assert( m_Data && m_Size );
            return m_Data[ m_Size - 1 ];
        }

        // Returns a pointer to the item at the front of the 
        // vector. Returns null if the vector is empty
        [[nodiscard]] constexpr T* begin()
        {
            assert( m_Data );
            return std::addressof( m_Data[ 0 ] );
        }

        // Returns a const pointer to the item at the front of the 
        // vector. Returns null if the vector is empty
        [[nodiscard]] constexpr const T* begin() const
        {
            assert( m_Data );
            return std::addressof( m_Data[ 0 ] );
        }

        // Returns a pointer that is one past the last item of the 
        // vector. Returns null if the vector is empty
        [[nodiscard]] constexpr T* end()
        {
            assert( m_Data );
            return std::addressof( m_Data[ m_Size ] );
        }

        // Returns a const pointer that is one past the last item of
        // the vector. Returns null if the vector is empty
        [[nodiscard]] constexpr const T* end() const
        {
            assert( m_Data );
            return std::addressof( m_Data[ m_Size ] );
        }

    private:

        constexpr void move( vector& other )
        {
            m_Capacity  = other.m_Capacity;
            m_Size      = other.m_Size;
            m_Data      = other.m_Data;
            other.reset();
        }

        // Reset function to reset the internal variables
        constexpr void reset()
        {
            m_Capacity  = 0;
            m_Size      = 0;
            m_Data      = nullptr;
        }

        constexpr void destruct_range( uint64_t first, uint64_t last )
        {
            // Check that the destruct is actually set
            assert( destruct );
            // Check that first and last are within the ranges of the 
            // array
            assert( first <= m_Size && last <= m_Size && first <= last );
            if( m_Data )
            {
                for( ; first != last; first++ )
                {
                    m_Data[first].~T();
                }
            }
        }

        constexpr void destroy()
        {
            // Check if there is anything to destroy
            //assert( [&](){ return m_Capacity ? m_Data : !m_Data} )
            assert( [&]{ return m_Capacity ? m_Data != nullptr : m_Data == nullptr; }() );

            clear();
            m_Capacity = 0;
            if ( m_Data ) 
            {
                free( m_Data );
            }
            m_Data = nullptr;
        }

        // Member variables
        uint64_t    m_Capacity{ 0 };
        uint64_t    m_Size{ 0 };
        T*          m_Data{ nullptr };
    };
} // namespace muggy::utils


#endif
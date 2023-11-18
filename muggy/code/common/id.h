//********************************************************************
//  File:    id.h
//  Date:    Mon, 13 Nov 2023: 02:09
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(ID_H)
#define ID_H

#include "common.h"

namespace muggy::id
{
    using id_type = uint32_t;

    namespace internal // Internal namespace
    {
        constexpr uint32_t generationBits( 8 );
        constexpr uint32_t indexBits( sizeof(id_type) * 8 - generationBits );
        constexpr id_type indexMask{ ( id_type(1) << indexBits ) - 1 };
        constexpr id_type generationMask{ ( id_type(1) << generationBits ) -1 };
    } // Internal namespace

    constexpr id_type invalid_id{ id_type(-1) };
    constexpr uint32_t min_deleted_elements( 1024 );

    using generation_type = std::conditional_t<internal::generationBits <= 16,
                                std::conditional_t<internal::generationBits <= 8,
                                uint8_t,
                                uint16_t>, uint32_t>;
    static_assert( sizeof( generation_type ) * 8 >= internal::generationBits );
    static_assert( ( sizeof( id_type ) - sizeof( generation_type ) ) > 0 );

    inline bool isValid( id_type id )
    {
        return id != invalid_id;
    }

    inline id_type index( id_type id )
    {
        id_type index( id & internal::indexMask );
        assert( index );
        return index;
    }

    inline id_type generation( id_type id )
    {
        return ( ( id >> internal::indexBits ) & 
                   internal::generationMask      );
    }

    inline id_type newGeneration( id_type id )
    {
        const id_type generation( id::generation( id ) - 1 );
        assert( generation < ( ( (uint64_t)1 << internal::generationBits) - 1) );
        return ( index(id) | ( generation << internal::indexBits ) );
    }

#ifdef DEBUG_BUILD
    namespace internal
    {
        struct id_base
        {
            constexpr explicit id_base( id_type id ) : m_Id(id) {}
            constexpr operator id_type() const { return m_Id; }
        private:
            id_type m_Id;
        };
    }
#define DEFINE_TYPED_ID(name)                                \
        struct name final : id::internal::id_base            \
        {                                                    \
            constexpr explicit name( id::id_type id)         \
                : id_base( id ) {}                           \
            constexpr name() : id_base( 0 ) {}               \
        }

#else
#define DEFINE_TYPED_ID(name)        using name = id::id_type;
#endif
}


#endif
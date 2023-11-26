//********************************************************************
//  File:    gameEntity.h
//  Date:    Fri, 24 Nov 2023: 21:29
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(GAME_ENTITY_H)
#define GAME_ENTITY_H

#include "../code/components/componentsCommon.h"
#include "componentTransform.h"

namespace muggy::game_entity
{
    DEFINE_TYPED_ID(entity_id);

    class entity
    {
    public:
        constexpr explicit entity( entity_id id ) : m_Id( id ) {}
        constexpr entity( ) : m_Id( id::invalid_id ) {}
        constexpr entity_id getId( ) const { return m_Id; }
        constexpr bool isValid( ) const { return id::isValid( m_Id ); }

        transform::component getTransform() const;
    private:
        entity_id m_Id;
    };
} // namespace muggy::game_entity


#endif
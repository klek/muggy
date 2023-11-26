//********************************************************************
//  File:    componentTransform.h
//  Date:    Fri, 24 Nov 2023: 22:20
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(COMPONENT_TRANSFORM_H)
#define COMPONENT_TRANSFORM_H

#include "../code/components/componentsCommon.h"

namespace muggy::transform
{
    DEFINE_TYPED_ID(transform_id);

    class component final
    {
    public:
        constexpr explicit component( transform_id id ) : m_Id( id ) {}
        constexpr component( ) : m_Id( id::invalid_id ) {}
        constexpr transform_id getId( ) const { return m_Id; }
        constexpr bool isValid( ) const { return id::isValid( m_Id ); }

        math::fv3d getPosition() const;
        math::fv4d getRotation() const;
        math::fv3d getScale() const;

    private:
        transform_id m_Id;
    };
} // namespace muggy::transform


#endif
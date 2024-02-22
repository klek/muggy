//********************************************************************
//  File:    componentScript.h
//  Date:    Sun, 18 Feb 2024: 13:19
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(COMPONENT_SCRIPT_H)
#define COMPONENT_SCRIPT_H

#include "../code/components/componentsCommon.h"

namespace muggy::script
{
    DEFINE_TYPED_ID(script_id);

    class component final
    {
    public:
        constexpr explicit component( script_id id ) : m_Id( id ) {}
        constexpr component( ) : m_Id( id::invalid_id ) {}
        constexpr script_id getId( ) const { return m_Id; }
        constexpr bool isValid( ) const { return id::isValid( m_Id ); }

    private:
        script_id m_Id;
    };
} // namespace muggy::transform

#endif
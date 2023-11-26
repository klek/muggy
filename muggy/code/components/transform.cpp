//********************************************************************
//  File:    transform.cpp
//  Date:    Fri, 24 Nov 2023: 22:29
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "transform.h"
#include "entity.h"

namespace muggy::transform
{
    namespace
    {
        utils::vector<math::fv3d>             positions;
        utils::vector<math::fv4d>             rotations;
        utils::vector<math::fv3d>             scales;
    } // namespace anonymous
    
    component createTransform( const init_info& info, game_entity::entity e )
    {
        // DEBUG: Check that the entity is valid!
        assert( e.isValid() );
        const id::id_type e_index{ id::index( e.getId() ) };

        // Check if we should reuse slots or create new slots
        if ( positions.size() > e_index )
        {
            // Reusing available slots
            positions[ e_index ] = math::fv3d( info.position );
            rotations[ e_index ] = math::fv4d( info.rotation );
            scales[ e_index ] = math::fv3d( info.scale );
        }
        else 
        {
            // Add new slots
            assert( positions.size() == e_index );
            positions.emplace_back( info.position );
            rotations.emplace_back( info.rotation );
            scales.emplace_back( info.scale );
        }

        return component( transform_id{ (id::id_type)positions.size() - 1 } );
    }

    void removeTransform( component c )
    {
        assert( c.isValid() );
    }

    math::fv3d component::getPosition() const
    {
        // DEBUG: Check that this component is valid
        assert( isValid() );
        return positions[ id::index( m_Id )];
    }

    math::fv4d component::getRotation() const
    {
        // DEBUG: Check that this component is valid
        assert( isValid() );
        return rotations[ id::index( m_Id )];
    }

    math::fv3d component::getScale() const
    {
        // DEBUG: Check that this component is valid
        assert( isValid() );
        return scales[ id::index( m_Id )];
    }

} // namespace muggy::transform

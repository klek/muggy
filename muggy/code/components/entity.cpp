//********************************************************************
//  File:    entity.cpp
//  Date:    Fri, 24 Nov 2023: 20:49
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "entity.h"
#include "transform.h"

namespace muggy::game_entity
{
    namespace 
    {
        utils::vector<transform::component> transforms;
        
        utils::vector<id::generation_type>  generations;
        utils::deque<entity_id>             freeIds;
    } // namespace anonymous
    
    entity createGameEntity( const entity_info& info )
    {
        // Check that the entity info contains a transform
        // which all entities must have
        assert( info.transform );
        if ( !info.transform )
        {
            // Return a default entity (ie invalid)
            return {};
        }

        entity_id id;

        // Check if we should reuse slots or create new slots
        if ( freeIds.size() > id::min_deleted_elements )
        {
            // Reusing available slots
            id = freeIds.front();
            assert( !isAlive( entity( id ) ) );
            freeIds.pop_front();
            id = entity_id{ id::newGeneration( id ) };
            ++generations[ id::index( id ) ];
            //generations[ id::index( id ) ];
        }
        else 
        {
            // Add new slots
            id = entity_id{ (id::id_type)generations.size() };
            generations.push_back( 0 );
            // Why not use emplace_back here?
            //generations.emplace_back( id );

            // Resize components
            // NOTE(klek): Here we call emplace_back instead of resize()
            //             to keep the number of memory allocations low
            transforms.emplace_back();
        }

        const entity newEntity{ id };
        const id::id_type index{ id::index(id) };

        // Create transform compontent
        assert( !transforms[ index ].isValid() );
        transforms[ index ] = transform::createTransform( *info.transform, 
                                                           newEntity );
        if ( !transforms[ index ].isValid() )
        {
            // Return a default entity (ie invalid)
            return {};
        }

        return newEntity;
    }

    void removeGameEntity( entity e )
    {
        const entity_id id{ e.getId() };
        const id::id_type index{ id::index( id ) };
        // Check that this entity is alive
        assert( isAlive(e) );
        if ( isAlive(e) )
        {
            // Remove transforms
            transform::removeTransform( transforms[ index ] );
            // Replace the slot with a default component (ie invalid)
            transforms[ index ] = {};
            freeIds.push_back( id );
        }
    }

    bool isAlive( entity e )
    {
        // DEBUG: Check that the entity is valid
        assert( e.isValid() );
        const entity_id id{ e.getId() };
        const id::id_type index{ id::index( id ) };
        // DEBUG: Check that index is withing the size of generations
        assert( index < generations.size() );
        // DEBUG: Check that the current generation is as expected
        //assert( generations[ index ] == id::generation( id ) );

        // If the current generation for this index is equal to the expected
        // generation and the transform for this entity is valid, then this 
        // entity is alive
        return ( generations[ index ] == id::generation( id ) && 
                 transforms[ index ].isValid()                  );
    }

    transform::component entity::getTransform() const
    {
        // DEBUG: Check that the entity is valid
        assert( isAlive( *this ) );
        const id::id_type index{ id::index( m_Id ) };
        return transforms[ index ];
    }

} // namespace muggy::entity

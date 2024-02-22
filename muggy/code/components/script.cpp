//********************************************************************
//  File:    script.cpp
//  Date:    Sun, 18 Feb 2024: 13:23
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "script.h"

namespace muggy::script
{
    namespace 
    {
        utils::vector<detail::scriptPtr>    entityScripts;
        utils::vector<id::id_type>          idMapping;

        utils::vector<id::generation_type>  generations;
        utils::deque<script_id>             freeIds;

        using scriptRegistry = std::unordered_map<size_t, detail::scriptCreator>;
        
        scriptRegistry& registry()
        {
            // NOTE(klek): This is put into a function because of 
            //             initialization order of static data. In 
            //             this way, we can make sure that the data
            //             is initialized before accessing it.
            static scriptRegistry reg;
            return reg;
        }

        bool exists( script_id id )
        {
            assert( id::isValid( id ) );
            const id::id_type index{ id::index(id) };
            assert( index < generations.size() && 
                    idMapping[index] < entityScripts.size() );
            assert( generations[index] == id::generation( id ) );
            return ( ( generations[index] == id::generation( id )     ) &&
                     ( entityScripts[ idMapping[ index ] ]            ) &&
                     ( entityScripts[ idMapping[ index ] ]->isValid() )   );
        }
    } // anonymous namespace 

    namespace detail
    {
        uint8_t registerScript( size_t tag, scriptCreator func )
        {
            bool result{ registry().insert( scriptRegistry::value_type{ tag, func } ).second };
            assert( result );
            return result;
        }

        scriptCreator getScriptCreator( size_t tag )
        {
            auto script = muggy::script::registry().find( tag );
            assert( script != muggy::script::registry().end() &&
                    script->first == tag );
            return script->second;
        }
    } // namespace detail
    
    
    component createScript( const init_info& info, game_entity::entity e )
    {
        assert( e.isValid() );
        assert( info.scriptCreator );

        script_id id;

        // Check if we should reuse slots or create new slots
        if ( freeIds.size() > id::min_deleted_elements )
        {
            // Reusing available slots
            id = freeIds.front();
            assert( !exists( id ) );
            freeIds.pop_front();
            id = script_id{ id::newGeneration( id ) };
            ++generations[ id::index( id ) ];
        }
        else
        {
            // Add new slots
            id = script_id{ (id::id_type)generations.size() };
            //id = script_id{ (id::id_type)idMapping.size() };
            generations.push_back( 0 );
            idMapping.emplace_back();
        }

        assert( id::isValid( id ) );

        entityScripts.emplace_back( info.scriptCreator( e ) );
        assert( entityScripts.back()->getId() == e.getId() );
        // Get the location of our new script, by subtracting the size with
        // one to get the last script we just added
        const id::id_type index{ (id::id_type)entityScripts.size() - 1 };
        idMapping[ id::index( id ) ] = index;
        
        return component{ id };
    }

    void removeScript( [[maybe_unused]] component c )
    {
        assert( c.isValid() );
        const script_id id{ c.getId() };
        // Get the index of the script we want to remove
        const id::id_type index{ idMapping[ id::index( id ) ] };
        // Get the id of the currently last script in the array
        const script_id lastId{ entityScripts.back()->getScript().getId() };
        // Remove the script we want (with the index from above)
        // This swaps the last script with the script we want to remove
        // and finally pops the last script
        utils::erase_unordered( entityScripts, index );
        // Remap the previous last script to the index we removed
        idMapping[ id::index( lastId ) ] = index;
        // Set the index at id to invalid
        idMapping[ id::index( id ) ] = id::invalid_id;
    }

    void update( float dt )
    {
        // Check that there are any scripts to update
        // Otherwise there is nothing to do here
        if ( entityScripts.size() > 0 )
        {
            for ( auto& ptr : entityScripts )
            {
                ptr->update( dt );
            }
        }
    }

} // namespace muggy::script

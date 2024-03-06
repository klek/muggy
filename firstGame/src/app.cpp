//********************************************************************
//  File:    app.cpp
//  Date:    Tue, 20 Feb 2024: 19:45
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "application.h"
#include "entityAPI.h"

namespace firstGame
{
    class gameApp : public muggy::application::application
    {
    public:
        //constexpr explicit gameApp( )
        gameApp( )
        {
            // Create the transform for a random entity
            muggy::transform_component transform{};

            // Create the script for a random entity
            muggy::script_component script{};
            script.script_creator = muggy::getScriptCreator("character_script");
            muggy::game_entity_descriptor e{};
            e.transform = transform;
            e.script = script;
            m_EntityId = muggy::createGameEntity( &e );
        }

        ~gameApp()
        {
            muggy::removeGameEntity( m_EntityId );
        }

    private:
        //muggy::game_entity::entity m_Entity;
        muggy::game_entity::entity_id m_EntityId;
    };

} // namespace firstGame

muggy::application::application* muggy::application::createApplication()
{
    return new firstGame::gameApp();
}
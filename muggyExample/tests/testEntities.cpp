//********************************************************************
//  File:    testEntities.cpp
//  Date:    Sat, 25 Nov 2023: 00:58
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#include "test.h"
#if TEST_ENTITIES
#include "testEntities.h"

#include <iostream>
#include <ctime>

//#if TEST_ENTITIES

using namespace muggy;

bool engineTest::initialize( void ) 
{
    srand( (uint32_t)time( nullptr ) );
    return true;
}

void engineTest::run ( void ) 
{
    do 
    {
        for ( uint32_t i = 0; i < 10000; i++ )
        {
            createRandom();
            removeRandom();
            m_TotalEntities = (uint32_t)m_Entities.size();
        }
        printResults();
    } while ( getchar() != 'q' );
    
}

void engineTest::shutdown( void ) 
{

}

void engineTest::createRandom( void )
{
    uint32_t count = rand() % 20;

    if ( m_Entities.empty() )
    {
        count = 1000;
    }

    transform::init_info transformInfo{};
    game_entity::entity_info entityInfo { &transformInfo };

    while ( count > 0 )
    {
        m_Added++;
        game_entity::entity e{ game_entity::createGameEntity(entityInfo) };
        assert( e.isValid() && id::isValid( e.getId() ) );
        m_Entities.push_back( e );
        assert( game_entity::isAlive( e ) );
        count--;
    }
}

void engineTest::removeRandom( void )
{
    uint32_t count = rand() % 20;

    if ( m_Entities.size() < 1000 ) return;
    while ( count > 0 )
    {
        const uint32_t index{ (uint32_t)rand() % (uint32_t)m_Entities.size() };
        const game_entity::entity e{ m_Entities[ index ] };
        assert( e.isValid() && id::isValid( e.getId() ) );
        if ( e.isValid() )
        {
            game_entity::removeGameEntity(e);
            m_Entities.erase( m_Entities.begin() + index );
            assert( !game_entity::isAlive( e ) );
            m_Removed++;
        }
        count--;
    }
}

void engineTest::printResults()
{
    std::cout << "Entities created: " << m_Added << "\n";
    std::cout << "Entities deleted: " << m_Removed << "\n";
}

#endif
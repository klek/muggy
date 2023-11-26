//********************************************************************
//  File:    testEntities.h
//  Date:    Sat, 25 Nov 2023: 00:55
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(TEST_ENTITIES_H)
#define TEST_ENTITIES_H

#include "test.h"
//#include "muggy.h"
#include "../../muggy/code/common/common.h"
#include "../../muggy/code/components/entity.h"
#include "../../muggy/code/components/transform.h"

class engineTest : public test
{
public:
    bool initialize( void ) override;
    void run ( void ) override;
    void shutdown( void ) override;

    // Additional functions for this test

private:
    void createRandom();
    void removeRandom();
    void printResults();

    bool m_IsRunning = true;
    // Need a vector for storing entities
    muggy::utils::vector<muggy::game_entity::entity> m_Entities;
    // Need a variable to keep track of added entities
    uint32_t m_Added = 0;
    // Need a variable to keep track of removed entities
    uint32_t m_Removed = 0;
    // Need a variable to keep track of total number of entitites
    uint32_t m_TotalEntities = 0;
};



#endif
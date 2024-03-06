//********************************************************************
//  File:    testFreelist.h
//  Date:    Sat, 03 Feb 2024: 05:11
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(TEST_FREELIST_H)
#define TEST_FREELIST_H

#include "test.h"

#include "../../muggy/code/common/common.h"
#include "../../muggy/code/utilities/freelist.h"

#define DEFAULT_ALLOC_SIZE      5

class var1
{
    var1()
     : m_TestVar1(0), m_Capacity(DEFAULT_ALLOC_SIZE)
    {
        // Allocate memory for data
        allocateData( m_Capacity );

        for ( uint32_t i = 0; i < m_Capacity; i++ )
        {
            m_Data[i] = m_TestVar1;
        }
    }

    var1( const uint32_t val )
     : m_TestVar1( val ), m_Capacity( DEFAULT_ALLOC_SIZE )
    {
        // Allocate memory for data
        allocateData( m_Capacity );

        for ( uint32_t i = 0; i < m_Capacity; i++ )
        {
            m_Data[i] = m_TestVar1;
        }
    }

    // Copy constructor
    var1( const var1& other )
     : m_TestVar1( other.m_TestVar1 ), m_Capacity( other.m_Capacity )
    {
        *this = other;
        std::cout << "Copy constructor" << std::endl;
    }

    // Move constructor
    var1( var1&& other )
     : m_TestVar1( other.m_TestVar1 ), m_Capacity( other.m_Capacity )
    {
        m_Data = other.m_Data;
        other.m_Data = nullptr;

        std::cout << "Move constructor" << std::endl;
    }

    // Copy assignment
    var1& operator=( const var1& other )
    {
        m_TestVar1 = other.m_TestVar1;
        m_Capacity = other.m_Capacity;

        // Allocate memory for data
        allocateData( m_Capacity );

        if ( m_Data )
        {
            for ( uint32_t i = 0; i < other.m_Capacity; i++ )
            {
                m_Data[i] = other.m_Data[i];
            }
        }

        std::cout << "Copy" << std::endl;
    }

    // Move assignment
    var1& operator=( var1&& other )
    {
        m_TestVar1 = other.m_TestVar1;
        m_Capacity = other.m_Capacity;

        m_Data = other.m_Data;
        other.m_Data = nullptr;

        std::cout << "Move" << std::endl;
    }

    ~var1()
    {
        // Dealloc the vector
        ::operator delete(m_Data, m_Capacity * sizeof(uint32_t) );
        delete[] m_Data;

        std::cout << "Destroyed" << std::endl;
    }

private:
    void allocateData( const uint32_t size )
    {
        // Allocate memory for data
        uint32_t* newBuf = (uint32_t*)::operator new( size * sizeof(uint32_t) );
//        uint32_t* newBuf = new uint32_t[ size ];

        if ( newBuf )
        {
            m_Data = newBuf;
        }
    }

    uint32_t m_TestVar1 = 0;
    uint32_t m_Capacity = 0;
    uint32_t* m_Data = nullptr ;
};

class engineTest : public test
{
public:
    bool initialize( void ) override;
    void run ( void ) override;
    void shutdown( void ) override;

    // Additional functions for this test

private:
    // Need a freelist to store items in
    muggy::utils::free_list<var1> m_Storage;
};


#endif
//********************************************************************
//  File:    application.h
//  Date:    Tue, 20 Feb 2024: 19:26
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(APPLICATION_H)
#define APPLICATION_H

#include "../common/myTypes.h"

namespace muggy::application
{
    class application
    {
    public:
        application( )
        {

        }
        virtual ~application( ) = default;

        uint32_t loadGameData( );
        uint32_t unloadGameData( );
    private:
    };

    // To be defined in the client/game code
    application* createApplication( );
} // namespace muggy::application



#endif
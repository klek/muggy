//********************************************************************
//  File:    openglCore.h
//  Date:    Mon, 13 Nov 2023: 01:27
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(OPENGL_H)
#define OPENGL_H

#include "openglCommon.h"

namespace muggy::graphics::opengl::core
{
    bool initialize( void );

    void shutdown(void );
}


#endif
//********************************************************************
//  File:    window.cpp
//  Date:    Mon, 13 Nov 2023: 01:58
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if INCLUDE_WINDOW_CPP
#include "window.h"

namespace muggy::platform
{
    void window::setFullScreen( bool isFullScreen ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );

        setWindowFullScreen( m_Id, isFullScreen );
    }

    /*
    void window::setWindowedFullScreen( bool isFullScreen ) const
    {

    }
    */

    bool window::isFullScreen( void ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );
        return isWindowFullScreen( m_Id );
    }

    void* window::handle( void ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );
        return getWindowHandle( m_Id );
    }

    void window::setCaption(const char* caption) const
    {
        // Check if this instance of id is valid
        assert( isValid() );

        setWindowTitle( m_Id, caption );
    }

    math::vec4d window::size() const
    {
        // Check if this instance of id is valid
        assert( isValid() );
        return getWindowSize( m_Id );
    }

    void window::resize( uint32_t width, uint32_t height ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );

        resizeWindow( m_Id, width, height );
    }

    uint32_t window::getWidth( void ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );

        math::vec4d size{ getWindowSize( m_Id ) };
        return size.z - size.x;
    }

    uint32_t window::getHeight( void ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );

        math::vec4d size{ getWindowSize( m_Id ) };
        return size.w - size.y;
    }

    bool window::isClosed( void ) const
    {
        // Check if this instance of id is valid
        assert( isValid() );

        return isWindowClosed( m_Id );
    }

}
#endif
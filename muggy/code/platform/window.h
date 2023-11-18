//********************************************************************
//  File:    window.h
//  Date:    Mon, 13 Nov 2023: 00:50
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(WINDOW_H)
#define WINDOW_H

#include "../common/common.h"
#include "../math/math.h"

namespace muggy::platform
{
    DEFINE_TYPED_ID(windowId);

    class window
    {
    public:
        constexpr explicit window( windowId id) : m_Id(id) {}
        constexpr window( ) : m_Id( id::invalid_id ) { }
        constexpr windowId getId( ) const { return m_Id; }
        //constexpr bool isValid( ) const { return id::isValid(m_Id); }
        bool isValid( ) const { return id::isValid(m_Id); }

        void setFullScreen( bool isFullScreen ) const;
        //void setWindowedFullScreen ( bool isFullScreen ) const;
        bool isFullScreen( void ) const;
        void* handle( void ) const;
        void setCaption(const char* caption) const;
        math::vec4d size( ) const;
        void resize( uint32_t width, uint32_t height ) const;
        uint32_t getWidth( void ) const;
        uint32_t getHeight( void ) const;
        bool isClosed( void ) const;

    private:
        windowId m_Id;
    };
}

#endif
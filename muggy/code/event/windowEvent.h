//********************************************************************
//  File:    windowEvent.h
//  Date:    Wed, 22 Nov 2023: 23:44
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(WINDOW_EVENT_H)
#define WINDOW_EVENT_H

#include "eventType.h"
#include "../math/math.h"
// Included window from platform
#include "../platform/window.h"

// TODO(klek): Included for debugging
#include <sstream>

namespace muggy::event
{
    class windowEvent : public event
    {
    public:
        platform::window_id getId() const { return m_Id; }
        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_APPLICATION |
                     eventCategory::EVENT_WINDOW        );
        }

    protected:
        windowEvent( const platform::window_id& id )
         : m_Id( id ) 
        {}

        platform::window_id m_Id{ id::invalid_id };
    };

    class windowCloseEvent : public windowEvent
    {
    public:
        windowCloseEvent( const platform::window_id& id )
         : windowEvent( id )
        {}

        static eventType getStaticType() 
        {
            return eventType::WINDOW_CLOSE;
        }
        virtual eventType getEventType() const override 
        {
            return getStaticType(); 
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override 
        {
            return "WINDOW_CLOSE";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": ";
            return ss.str();
        }
        //************************************************************

    };

    class windowResizeEvent : public windowEvent
    {
    public:
        windowResizeEvent( const platform::window_id& id, 
                           const uint32_t& width, 
                           const uint32_t& height )
         : 
            windowEvent( id ),
            m_Width( width ),
            m_Height( height )
        {}

        uint32_t getWidth() const { return m_Width; }
        uint32_t getHeight() const { return m_Height; }

        static eventType getStaticType() 
        {
            return eventType::WINDOW_RESIZE;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "WINDOW_RESIZE";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << m_Width << ", " << m_Height;
            return ss.str();
        }
        //************************************************************

    private:
        uint32_t m_Width;
        uint32_t m_Height;
    };

    class windowFocusEvent : public windowEvent
    {
    public:
        windowFocusEvent( const platform::window_id id, 
                          const bool focused )
         : 
            windowEvent( id ),
            m_Focused( focused )
        {}

        bool isFocused() const { return m_Focused; }

        static eventType getStaticType() 
        {
            return eventType::WINDOW_FOCUS;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "WINDOW_FOCUS";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << ( m_Focused ? "FOCUSED" : "LOST_FOCUS" );
            return ss.str();
        }
        //************************************************************

    private:
        bool m_Focused = false;
    };

    class windowMovedEvent : public windowEvent
    {
    public:
        windowMovedEvent( const platform::window_id& id, 
                          const math::POINT& pos )
         : 
            windowEvent( id ),
            m_Pos( pos )
        {}

        uint32_t getWindowXPosition() const { return m_Pos.left; }
        uint32_t getWindowYPosition() const { return m_Pos.top; }

        static eventType getStaticType() 
        {
            return eventType::WINDOW_MOVED;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "WINDOW_MOVED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << m_Pos.left << ", " << m_Pos.top;
            return ss.str();
        }
        //************************************************************

    private:
        math::POINT m_Pos{ 0, 0 };
    };

} // namespace muggy::event



#endif
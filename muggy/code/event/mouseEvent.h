//********************************************************************
//  File:    mouseEvent.h
//  Date:    Wed, 22 Nov 2023: 23:11
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(MOUSE_EVENT_H)
#define MOUSE_EVENT_H

#include "eventType.h"
// Included window from platform
#include "../platform/window.h"

// TODO(klek): Included for debugging
#include <sstream>

namespace muggy::event
{
    class mouseButtonEvent : public event
    {
    public:
        uint32_t getMouseButton() const { return m_Button; }
        platform::window_id getId() const { return m_Id; }

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_INPUT | 
                     eventCategory::EVENT_MOUSE |
                     eventCategory::EVENT_MOUSE_BUTTON );
        }

    protected:
        mouseButtonEvent( const platform::window_id& id, 
                          const uint32_t button )
         : 
            m_Id( id ), 
            m_Button( button )
        {}

        // NOTE(klek): Might want to set this to a mouseCode class later
        uint32_t m_Button;
        platform::window_id m_Id{ id::invalid_id };
    };

    class mouseButtonPressedEvent : public mouseButtonEvent
    {
    public:
        mouseButtonPressedEvent( const platform::window_id& id, 
                                 const uint32_t button )
         : 
            mouseButtonEvent( id, button )
        {}

        static eventType getStaticType() 
        {
            return eventType::MOUSE_BUTTON_PRESSED;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "MOUSE_BUTTON_PRESSED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << m_Button;
            return ss.str();
        }
        //************************************************************

    };

    class mouseButtonReleasedEvent : public mouseButtonEvent
    {
    public:
        mouseButtonReleasedEvent( const platform::window_id& id, 
                                  const uint32_t button )
         : 
            mouseButtonEvent( id, button )
        {}

        static eventType getStaticType() 
        {
            return eventType::MOUSE_BUTTON_RELEASED;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "MOUSE_BUTTON_RELEASED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << m_Button;
            return ss.str();
        }
        //************************************************************

    };

    class mouseMovedEvent : public event
    {
    public:
        mouseMovedEvent( const platform::window_id& id, 
                         const float x, 
                         const float y )
         : 
            m_Id( id ),
            m_MouseX( x ),
            m_MouseY( y )
        {}

        platform::window_id getId() const { return m_Id; }
        float getXPosition() const { return m_MouseX; }
        float getYPosition() const { return m_MouseY; }

        static eventType getStaticType() 
        {
            return eventType::MOUSE_MOVED;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "MOUSE_MOVED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }
        //************************************************************

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_INPUT | 
                     eventCategory::EVENT_MOUSE );
        }

    private:
        float m_MouseX;
        float m_MouseY;

        platform::window_id m_Id{ id::invalid_id };
    };

    class mouseScrolledEvent : public event
    {
    public:
        mouseScrolledEvent( const platform::window_id& id, 
                            const float xOffset, 
                            const float yOffset )
        : 
            m_Id( id ),
            m_XOffset( xOffset ),
            m_YOffset( yOffset )
        {}

        platform::window_id getId() const { return m_Id; }
        float getXOffset() const { return m_XOffset; }
        float getYOffset() const { return m_YOffset; }

        static eventType getStaticType() 
        {
            return eventType::MOUSE_SCROLLED;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "MOUSE_SCROLLED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << " event for ID = " << getId() << ": " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }
        //************************************************************

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_INPUT | 
                     eventCategory::EVENT_MOUSE );
        }

    private:
        float m_XOffset;
        float m_YOffset;
        platform::window_id m_Id{ id::invalid_id };
    };

} // namespace muggy::event


#endif
//********************************************************************
//  File:    keyEvent.h
//  Date:    Wed, 22 Nov 2023: 04:39
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(KEY_EVENT_H)
#define KEY_EVENT_H

#include "eventType.h"
// Included window from platform
#include "../platform/window.h"

// TODO(klek): Included for debugging
#include <sstream>


namespace muggy::event
{
    class keyEvent : public event
    {
    public:
        uint32_t getKeyCode() const { return m_KeyCode; }
        platform::window_id getId() const { return m_Id; }

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_INPUT | 
                     eventCategory::EVENT_KEYBOARD );
        }

    protected:
        keyEvent( const platform::window_id& id, 
                  const uint32_t keyCode )
         : 
            m_Id( id ), 
            m_KeyCode( keyCode )
        {}
        
        // NOTE(klek): Might want to set this to a keyCode class later
        uint32_t m_KeyCode;
        platform::window_id m_Id{ id::invalid_id };
    };

    class keyPressedEvent : public keyEvent
    {
    public:
        keyPressedEvent( const platform::window_id& id, 
                         const uint32_t keyCode, 
                         const bool repeatCount )
         : 
            keyEvent( id, keyCode ), 
            m_RepeatCount( repeatCount )
        {}

        uint32_t getRepeatCount() const { return m_RepeatCount; }

        static eventType getStaticType() 
        {
            return eventType::KEY_PRESSED;
        }
        virtual eventType getEventType() const override 
        {
            return getStaticType(); 
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override 
        {
            return "KEY_PRESSED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() <<  " event for ID = " << getId() << ": " << m_KeyCode << " ( repeat = " << m_RepeatCount << " )";
            return ss.str();
        }
        //************************************************************

    private:
        bool m_RepeatCount;
    };

    class keyReleasedEvent : public keyEvent
    {
    public:
        keyReleasedEvent( const platform::window_id& id, 
                          const uint32_t keyCode )
         : 
            keyEvent( id, keyCode )
        {}

        static eventType getStaticType() 
        {
            return eventType::KEY_RELEASED;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override 
        {
            return "KEY_RELEASED";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() <<  " event for ID = " << getId() << ": ";
            return ss.str();
        }
        //************************************************************

    };
} // namespace muggy::event



#endif
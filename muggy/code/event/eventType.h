//********************************************************************
//  File:    event.h
//  Date:    Wed, 22 Nov 2023: 04:20
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(EVENT_TYPE_H)
#define EVENT_TYPE_H

#include "../common/common.h"

namespace muggy::event
{
	// Events are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then 
    // and there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

    enum class eventType : uint32_t
    {
        NONE = 0,
        // Window events
        WINDOW_CLOSE            , //=  1, 
        WINDOW_RESIZE           , //=  2, 
        WINDOW_FOCUS            , //=  3, 
        WINDOW_LOST_FOCUS       , //=  4, 
        WINDOW_MOVED            , //=  5,
        // Application events
        APPLICATION_TICK        , //=  6,
        APPLICATION_UPDATE      , //=  7,
        APPLICATION_RENDER      , //=  8,
        // Keyboard events
        KEY_PRESSED             , //=  9,
        KEY_RELEASED            , //= 10,
        // Mouse events
        MOUSE_BUTTON_PRESSED    , //= 11,
        MOUSE_BUTTON_RELEASED   , //= 12,
        MOUSE_MOVED             , //= 13,
        MOUSE_SCROLLED          , //= 14,
        // Network events
        NETWORK_PKT_RECEIVED    , //= 15,
        NETWORK_PKT_SENT        , //= 16,
        NETWORK_PING            , //= 17
    };

    enum eventCategory : uint32_t
    {
        NONE = 0,
        EVENT_APPLICATION   = BIT(0),
        EVENT_WINDOW        = BIT(1),
        EVENT_INPUT         = BIT(2),
        EVENT_KEYBOARD      = BIT(3),
        EVENT_MOUSE         = BIT(4),
        EVENT_MOUSE_BUTTON  = BIT(5),
        EVENT_NETWORK       = BIT(6)
    };

    class event
    {
    public:
        bool m_Handled = false;

        virtual ~event() = default;

        virtual eventType getEventType() const = 0;
        virtual uint32_t getEventCategoryFlags() const = 0;
        
        // TODO(klek): For debugging only
        virtual const char* getName() const = 0;
        virtual std::string toString() const { return getName(); }

        bool isInEventCategory( eventCategory category ) 
        {
            return getEventCategoryFlags() & category; 
        }

        // Overload operator<< for output of events
        friend std::ostream& operator<<( std::ostream& stream, const event& e )
        {
            return stream << e.toString();
        }

    // private:
    //     bool m_Handled = false;
    };

    class eventDispatcher
    {
    public:
        eventDispatcher( event& event )
         : m_Event( event )
        {}

        template <typename T, typename F>
        bool dispatch( const F& func )
        {
            if ( m_Event.getEventType() == T::getStaticType() )
            {
                m_Event.m_Handled |= func( static_cast<T&>( m_Event ) );
                return true;
            }

            return false;
        }

    private:
        event& m_Event;
    };

} // namespace muggy::event



#endif
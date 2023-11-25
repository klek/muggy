//********************************************************************
//  File:    applicationEvent.h
//  Date:    Thu, 23 Nov 2023: 00:14
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(APPLICATION_EVENT_H)
#define APPLICATION_EVENT_H

#include "eventType.h"
// TODO(klek): Included for debugging
#include <sstream>

namespace muggy::event
{
    class appTickEvent : public event
    {
    public:
        appTickEvent() = default;

        static eventType getStaticType() 
        {
            return eventType::APPLICATION_TICK;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "APPLICATION_TICK";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << ": ";
            return ss.str();
        }
        //************************************************************

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_APPLICATION );
        }

    };

    class appUpdateEvent : public event
    {
    public:
        appUpdateEvent() = default;

        static eventType getStaticType() 
        {
            return eventType::APPLICATION_UPDATE;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "APPLICATION_UPDATE";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << ": ";
            return ss.str();
        }
        //************************************************************

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_APPLICATION );
        }

    };

    class appRenderEvent : public event
    {
    public:
        appRenderEvent() = default;

        static eventType getStaticType() 
        {
            return eventType::APPLICATION_RENDER;
        }
        virtual eventType getEventType() const override
        {
            return getStaticType();
        }

        //************************************************************
        // TODO(klek): For debugging only
        virtual const char* getName() const override
        {
            return "APPLICATION_RENDER";
        };
        std::string toString() const override 
        {
            std::stringstream ss;
            ss << getName() << ": ";
            return ss.str();
        }
        //************************************************************

        virtual uint32_t getEventCategoryFlags() const override 
        {
            return ( eventCategory::EVENT_APPLICATION );
        }

    };

} // namespace muggy::event


#endif
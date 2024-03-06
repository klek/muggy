//********************************************************************
//  File:    event.h
//  Date:    Thu, 23 Nov 2023: 01:52
//  Version: 
//  Author:  klek
//  Notes:   
//********************************************************************

#if !defined(EVENT_H)
#define EVENT_H

#include "eventType.h"
#include "applicationEvent.h"
#include "windowEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include <functional>


//using evFnCallback = std::function<void(muggy::event::event&)>;
using evFnCallback = void(*)( muggy::event::event& );


#endif
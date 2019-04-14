#pragma once

#include "EventHandler.h"

class EventHandlerMain : public EventHandler
{
public:
    EventHandlerMain();
    virtual ~EventHandlerMain();

    virtual void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value);
};

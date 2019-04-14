#pragma once

#include <Rocket/Core/EventListenerInstancer.h>

class EventInstancer : public Rocket::Core::EventListenerInstancer
{
public:
    EventInstancer();
    virtual ~EventInstancer();

    // Instances a new event handle
    virtual Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element);

    // Destroy the instancer
    virtual void Release();
};

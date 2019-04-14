#include "EventInstancer.h"
#include "Event.h"

EventInstancer::EventInstancer()
{}

EventInstancer::~EventInstancer()
{}

Rocket::Core::EventListener* EventInstancer::InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element)
{
    return new Event(value);
}

void EventInstancer::Release()
{
    delete this;
}

#include "Event.h"
#include "EventManager.h"

Event::Event(const Rocket::Core::String& value) : value(value)
{}

Event::~Event()
{}

void Event::ProcessEvent(Rocket::Core::Event& event)
{
    EventManager::ProcessEvent(event, value);
}

void Event::OnDetach(Rocket::Core::Element* element)
{
    ROCKET_UNUSED(element);
    delete this;
}

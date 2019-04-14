#pragma once

#include <Rocket/Core/EventListener.h>

class Event : public Rocket::Core::EventListener
{
public:
    Event(const Rocket::Core::String& value);
    virtual ~Event();

    // Send the events value
    virtual void ProcessEvent(Rocket::Core::Event& event);

    // Destroy event
    virtual void OnDetach(Rocket::Core::Element* element);

private:
    Rocket::Core::String value;
};

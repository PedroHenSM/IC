#pragma once

#include <Rocket/Core/String.h>

namespace Rocket {
    namespace Core {
        class Event;
    }
}

class EventHandler
{
public:
	virtual ~EventHandler();
	virtual void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value) = 0;
};

#pragma once

#include <Rocket/Core/Event.h>
#include <Rocket/Core/Context.h>
#include "EventHandler.h"

#include "Renderer.h"

class EventManager
{
public:
	static void Shutdown();

	static void RegisterEventHandler(const Rocket::Core::String& handler_name, EventHandler* handler);

	static void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value);

	static bool LoadWindow(const Rocket::Core::String& window_name);

	static void SetContext(Rocket::Core::Context* context);

	static void SetRenderer(Library::Renderer* renderer);

private:
    static Rocket::Core::Context* sContext;
    static Library::Renderer* sRenderer;

    static Rocket::Core::Element* sFocusedElement;

	EventManager();
	~EventManager();
};

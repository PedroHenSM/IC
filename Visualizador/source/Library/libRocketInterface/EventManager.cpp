#include "EventManager.h"
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include "EventHandler.h"
#include <map>

#include <iostream>

// The game's element context (declared in main.cpp).
Rocket::Core::Context* EventManager::sContext = nullptr;
Rocket::Core::Element* EventManager::sFocusedElement = nullptr;
Library::Renderer* EventManager::sRenderer = nullptr;

// The event handler for the current screen. This may be NULL if the current screen has no specific functionality.
static EventHandler* event_handler = NULL;

// The event handlers registered with the manager.
typedef std::map< Rocket::Core::String, EventHandler* > EventHandlerMap;
EventHandlerMap event_handlers;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::SetContext(Rocket::Core::Context* context)
{
    sContext = context;
}

void EventManager::SetRenderer(Library::Renderer* renderer)
{
    sRenderer = renderer;
}

// Releases all event handlers registered with the manager.
void EventManager::Shutdown()
{
	for (EventHandlerMap::iterator i = event_handlers.begin(); i != event_handlers.end(); ++i)
		delete (*i).second;

	event_handlers.clear();
	event_handler = NULL;
}

// Registers a new event handler with the manager.
void EventManager::RegisterEventHandler(const Rocket::Core::String& handler_name, EventHandler* handler)
{
	// Release any handler bound under the same name.
	EventHandlerMap::iterator iterator = event_handlers.find(handler_name);
	if (iterator != event_handlers.end())
		delete (*iterator).second;

	event_handlers[handler_name] = handler;
}

// Processes an event coming through from Rocket.
void EventManager::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
	Rocket::Core::StringList commands;
	Rocket::Core::StringUtilities::ExpandString(commands, value, ';');
	for (size_t i = 0; i < commands.size(); ++i)
	{
		// Check for a generic 'load' or 'exit' command.
		Rocket::Core::StringList values;
		Rocket::Core::StringUtilities::ExpandString(values, commands[i], ' ');

		if (values[0] == "load" &&
 			values.size() > 1)
		{
			// Load the window.
			LoadWindow(values[1]);
		}
		else if (values[0] == "close")
		{
			Rocket::Core::ElementDocument* target_document = NULL;

			if (values.size() > 1)
				target_document = sContext->GetDocument(values[1].CString());
			else
				target_document = event.GetTargetElement()->GetOwnerDocument();

			if (target_document != NULL)
				target_document->Close();
		}
		else if (values[0] == "toggle")
		{
            Rocket::Core::ElementDocument* document = event.GetTargetElement()->GetOwnerDocument();
            Rocket::Core::Element* target = document->GetElementById(values[1]);

            if(target)
            {
                if(sFocusedElement == target)
                {
                    target->SetProperty("display", "none");
                    sFocusedElement = nullptr;
                }
                else
                {
                    target->SetProperty("display", "block");
                    sFocusedElement = target;
                }
            }
		}
		else if (values[0] == "fileselector")
		{
            sRenderer->ProcessEvent("ReadData\0");
		}
		else if (values[0] == "exit")
		{
			sRenderer->Exit();
		}
		else if (values[0] == "updateView")
		{
            // Check if there are any dropdown panel open
            if(sFocusedElement)
            {
                if(event.GetTargetElement()->GetParentNode() != sFocusedElement->GetParentNode())
                {
                    sFocusedElement->SetProperty("display", "none");
                    sFocusedElement = nullptr;
                }
            }

            // If the target is the body, the user is using the viewport
            sRenderer->SetUpdateCamera(false);
            if(event.GetTargetElement()->GetTagName() == "body")
            {
                if(event.GetType() == "mousedown")
                {
                    sRenderer->SetUpdateCamera(true);
                }
                else
                {
                    sRenderer->SetUpdateCamera(false);
                }
            }
		}
		else
		{
			if (event_handler != NULL)
				event_handler->ProcessEvent(event, commands[i]);
		}
	}
}

// Loads a window and binds the event handler for it.
bool EventManager::LoadWindow(const Rocket::Core::String& window_name)
{
	// Set the event handler for the new screen, if one has been registered.
	EventHandler* old_event_handler = event_handler;
	EventHandlerMap::iterator iterator = event_handlers.find(window_name);
	if (iterator != event_handlers.end())
		event_handler = (*iterator).second;
	else
		event_handler = NULL;

	// Attempt to load the referenced RML document.
	//Rocket::Core::String document_path = Rocket::Core::String("data/") + window_name + Rocket::Core::String(".rml");
	Rocket::Core::ElementDocument* document = sContext->LoadDocument(window_name.CString());
	if (document == NULL)
	{
		event_handler = old_event_handler;
		return false;
	}

	// Set the element's title on the title; IDd 'title' in the RML.
	Rocket::Core::Element* title = document->GetElementById("title");
	if (title != NULL)
		title->SetInnerRML(document->GetTitle());

	document->Focus();
	document->Show();

	// Remove the caller's reference.
	document->RemoveReference();

	return true;
}

#pragma once

#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Input.h>

#include <GLFW/glfw3.h>

class RendererSystemInterface : public Rocket::Core::SystemInterface
{
public:
    Rocket::Core::Input::KeyIdentifier TranslateKey(int glfwKey);
    int TranslateMouseButton(unsigned char button);
	int GetKeyModifiers(int modifiers);
	float GetElapsedTime();
    bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
};

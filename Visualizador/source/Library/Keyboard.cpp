#include "Keyboard.h"
#include "Renderer.h"
#include "RendererTime.h"

#include <cstdlib>

namespace Library
{
	RTTI_DEFINITIONS(Keyboard)

	Keyboard::Keyboard(Renderer& renderer) : RendererComponent(renderer)
	{
        //memset(mLastKeyboardKeys, 0, 256 * sizeof(char));
        //memset(mCurrentKeyboardKeys, 0, 256 * sizeof(char));
	}

	Keyboard::~Keyboard()
	{}

	void Keyboard::UpdateKey(int key, int action)
	{

	}

	bool Keyboard::IsKeyUp(int key) const
	{
		return glfwGetKey(&(mRenderer->Window()), key) == GLFW_RELEASE;
	}

	bool Keyboard::IsKeyDown(int key) const
	{
		return glfwGetKey(&(mRenderer->Window()), key) == GLFW_PRESS;
	}
}

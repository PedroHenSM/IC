#include "Mouse.h"
#include "Renderer.h"

#include <cstring>

namespace Library
{
	RTTI_DEFINITIONS(Mouse)

	Mouse::Mouse(Renderer& renderer)
		: RendererComponent(renderer), mCurrentState(),
		mLastState(), mX(0.0), mY(0.0), mWheel(0.0)
	{}

	Mouse::~Mouse()
	{
	}

	MouseState Mouse::CurrentMouseState()
	{
		return mCurrentState;
	}

	MouseState Mouse::LastMouseState()
	{
		return mLastState;
	}

	void Mouse::Update(const RendererTime& rendererTime)
	{
		memcpy(&mLastState, &mCurrentState, sizeof(mCurrentState));

		GLFWwindow& window = mRenderer->Window();

		for (int i = 0; i < 4; i++)
		{
			mCurrentState.buttons[i] = glfwGetMouseButton(&window, i);
		}
		glfwGetCursorPos(&window, &mCurrentState.x, &mCurrentState.y);

		mX = mCurrentState.x - mLastState.x;
		mY = mCurrentState.y - mLastState.y;
		mWheel = mCurrentState.scroll - mLastState.scroll;
	}

	float Mouse::X() const
	{
		return (float)mCurrentState.x;
	}

	float Mouse::Y() const
	{
		return (float)mCurrentState.y;
	}

	float Mouse::Wheel() const
	{
		return (float)mWheel;
	}

	float Mouse::deltaX() const
	{
		return (float)mX;
	}

	float Mouse::deltaY() const
	{
		return (float)mY;
	}

	bool Mouse::IsButtonUp(MouseButtons button) const
	{
		return mCurrentState.buttons[button] == GLFW_RELEASE;
	}

	bool Mouse::IsButtonDown(MouseButtons button) const
	{
		return mCurrentState.buttons[button] != GLFW_RELEASE;
	}

	bool Mouse::WasButtonUp(MouseButtons button) const
	{
		return mLastState.buttons[button] == GLFW_RELEASE;
	}

	bool Mouse::WasButtonDown(MouseButtons button) const
	{
		return mLastState.buttons[button] != GLFW_RELEASE;
	}

	bool Mouse::WasButtonPressedThisFrame(MouseButtons button) const
	{
		return WasButtonUp(button) && IsButtonDown(button);
	}

	bool Mouse::WasButtonReleasedThisFrame(MouseButtons button) const
	{
		return WasButtonDown(button) && IsButtonUp(button);
	}

	bool Mouse::IsButtonHeldDown(MouseButtons button) const
	{
		return WasButtonDown(button) && IsButtonDown(button);
	}

	void Mouse::UpdadeWheel(double wheel)
	{
		mCurrentState.scroll += (long)wheel;
	}

}

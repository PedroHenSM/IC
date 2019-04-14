#pragma once

#include "RendererComponent.h"

namespace Library
{
	class RendererTime;

	enum MouseButtons
	{
		MouseButtonsLeft = 0,
		MouseButtonsRight = 1,
		MouseButtonsMiddle = 2,
		MouseButtonsX1 = 3
	};

	typedef struct _MouseState
	{
	    _MouseState() : x(0), y(0), scroll(0)
	    { for(int i = 0; i < 4; i++) buttons[i] = 0; }
		double x, y;
		long scroll;
		unsigned char buttons[4];
	} MouseState;

	class Mouse : public RendererComponent
	{
		RTTI_DECLARATIONS(Mouse, RendererComponent)

	public:
		Mouse(Renderer& renderer);
		~Mouse();

		MouseState CurrentMouseState();
		MouseState LastMouseState();

		virtual void Update(const RendererTime& rendererTime) override;

		float X() const;
		float Y() const;
		float Wheel() const;

		float deltaX() const;
		float deltaY() const;

		bool IsButtonUp(MouseButtons button) const;
		bool IsButtonDown(MouseButtons button) const;
		bool WasButtonUp(MouseButtons button) const;
		bool WasButtonDown(MouseButtons button) const;
		bool WasButtonPressedThisFrame(MouseButtons button) const;
		bool WasButtonReleasedThisFrame(MouseButtons button) const;
		bool IsButtonHeldDown(MouseButtons button) const;

		void UpdadeWheel(double wheel);

	private:
		Mouse();

		MouseState mCurrentState;
		MouseState mLastState;

		double mX;
		double mY;
		double mWheel;

	};
}

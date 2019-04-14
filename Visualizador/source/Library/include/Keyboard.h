#pragma once

#include "RendererComponent.h"

namespace Library
{
	class Keyboard : public RendererComponent
	{
		RTTI_DECLARATIONS(Keyboard, RendererComponent)

	public:
		Keyboard(Renderer& renderer);
		~Keyboard();

		bool IsKeyUp(int key) const;
		bool IsKeyDown(int key) const;

		void UpdateKey(int key, int action);

	private:
		Keyboard();

		char mLastKeyboardKeys[256];
		char mCurrentKeyboardKeys[256];

		Keyboard(const Keyboard& rhs);
		Keyboard& operator=(const Keyboard& rhs);
	};
}

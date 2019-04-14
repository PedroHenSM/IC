#pragma once

#include "Common.h"

#include "RendererTime.h"
#include "RendererClock.h"
#include "ServiceContainer.h"
#include "GBuffer.h"

#include "Shader.h"
#include "RendererObject.h"

namespace Library
{
	class RendererComponent;
	class Keyboard;
	class Mouse;

	class Renderer
	{
	public:
		Renderer(const std::string& windowTitle);
		virtual ~Renderer();

		const std::string& WindowTitle() const;
		GLFWwindow& Window() const;
		int ScreenWidth() const;
		int ScreenHeight() const;

		float AspectRatio() const;
		bool IsFullScreen() const;

		const std::vector<RendererComponent*>& Components() const;
		const ServiceContainer& Services() const;

		virtual void Run();
		virtual void Exit();
		virtual void Initialize();
		virtual void Update(const RendererTime& rendererTime);
		virtual void Draw(const RendererTime& rendererTime);
		virtual void Resize(int width, int height);
		virtual void Input(int key, int scanCode, int action, int mod);

	protected:
		virtual void InitializeWindow();
		virtual void Shutdown();

		static const unsigned int DefaultScreenWidth;
		static const unsigned int DefaultScreenHeight;

		std::string mWindowTitle;

		unsigned int mScreenWidth;
		unsigned int mScreenHeight;

		RendererClock mRendererClock;
		RendererTime mRendererTime;

		bool mIsFullScreen;
		std::vector<RendererComponent*> mComponents;
		ServiceContainer mServices;

		GLFWwindow* mWindow;
		Keyboard* mKeyboard;
		Mouse* mMouse;

		GBuffer mGeometryBuffer;

		RendererObject* mGO;
		Shader* mShader;

	private:
		Renderer(const Renderer& rhs);
		Renderer& operator=(const Renderer& rhs);

		std::string GetWindowTitle(int frames);

		static Renderer* staticRenderer;
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double x, double y);
		static void cursorCallback(GLFWwindow* window, double xPos, double yPos);
		static void resizeCallback(GLFWwindow* window, int width, int height);
		static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mod);



	};
}

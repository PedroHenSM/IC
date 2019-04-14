#include "Renderer.h"
#include "RendererComponent.h"
#include "DrawableComponent.h"
#include "ServiceContainer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"

#include <iostream>
#include <typeinfo>
#include <string>
#include <sstream>

namespace Library
{
	const unsigned int Renderer::DefaultScreenHeight = 768;
	const unsigned int Renderer::DefaultScreenWidth = 1024;

	Renderer* Renderer::staticRenderer = nullptr;

	Renderer::Renderer(const std::string & windowTitle)
		: mWindowTitle(windowTitle), mScreenWidth(DefaultScreenWidth), mScreenHeight(DefaultScreenHeight), mRendererClock(),
		  mRendererTime(), mIsFullScreen(false), mWindow(nullptr), mKeyboard(nullptr), mMouse(nullptr),
		  mGeometryBuffer(DefaultScreenWidth, DefaultScreenHeight)
	{
		staticRenderer = this;
	}

	Renderer::~Renderer()
	{
	}

	const std::string & Renderer::WindowTitle() const
	{
		return mWindowTitle;
	}

	GLFWwindow & Renderer::Window() const
	{
		return *mWindow;
	}

	int Renderer::ScreenWidth() const
	{
		return mScreenWidth;
	}

	int Renderer::ScreenHeight() const
	{
		return mScreenHeight;
	}

	float Renderer::AspectRatio() const
	{
		return static_cast<float>(mScreenWidth)/mScreenHeight;
	}

	bool Renderer::IsFullScreen() const
	{
		return mIsFullScreen;
	}

	const std::vector<RendererComponent*>& Renderer::Components() const
	{
		return mComponents;
	}

	const ServiceContainer& Renderer::Services() const
	{
		return mServices;
	}

	void Renderer::Run()
	{
		InitializeWindow();
		Initialize();

		mRendererClock.Reset();

		while (!glfwWindowShouldClose(mWindow))
		{
			glfwPollEvents();

			mRendererClock.UpdateRendererTime(mRendererTime);
			Update(mRendererTime);
			Draw(mRendererTime);

			glfwSwapBuffers(mWindow);
		}

		Shutdown();
	}

	void Renderer::Exit()
	{
		glfwSetWindowShouldClose(mWindow, 1);
	}

	void Renderer::Initialize()
	{
		// Initialize Keyboard
		mKeyboard = new Keyboard(*this);
		mComponents.push_back(mKeyboard);
		mServices.AddService(Keyboard::TypeIdClass(), mKeyboard);

		// Initialize Mouse
		mMouse = new Mouse(*this);
		mComponents.push_back(mMouse);
		mServices.AddService(Mouse::TypeIdClass(), mMouse);

		/*// Initilize Camera
		mCamera = new Camera(*this);
		mComponents.push_back(mCamera);
		mServices.AddService(Camera::TypeIdClass(), mCamera);*/

        // Initialize the G-Buffer
		//mGeometryBuffer.Initialize();

		//mShader = new Shader("../../content/vert.glsl", "../../content/frag.glsl");

		//mGO = new RendererObject(*this, *mCamera, *mShader);
		//mComponents.push_back(mGO);

		for (RendererComponent* component : mComponents)
		{
			component->Initialize();
		}
	}

	void Renderer::Shutdown()
	{
		for (RendererComponent* component : mComponents)
		{
			if (component != nullptr)
			{
				delete component;
				component = nullptr;
			}
		}

		if (mWindow != nullptr)
		{
			glfwDestroyWindow(mWindow);
		}
		glfwTerminate();
	}

	void Renderer::Update(const RendererTime& rendererTime)
	{
		if (mKeyboard->IsKeyDown(GLFW_KEY_ESCAPE))
		{
			Exit();
		}

		static double time = 0.0;
		static int frames = 0;

		frames++;
		time += rendererTime.ElapsedRendererTime();
		if (time > 1)
		{
		    std::string windowTitle = GetWindowTitle(frames);
		    glfwSetWindowTitle(mWindow, windowTitle.c_str());
			/*std::cout << "FPS: " << frames << std::endl;
			std::cout << "Mouse: " << mMouse->X() << ", " << mMouse->Y() << std::endl;
			std::cout << "Buttons: " << mMouse->IsButtonDown(MouseButtonsLeft) << " " << mMouse->IsButtonDown(MouseButtonsRight) << " " << mMouse->IsButtonDown(MouseButtonsMiddle) << std::endl;
			std::cout << "Scroll: " << mMouse->Wheel() << std::endl;*/
			frames = 0;
			time = 0;
		}

		for (RendererComponent* component : mComponents)
		{
			if (component->Enabled())
			{
				component->Update(rendererTime);
			}
		}
	}

	void Renderer::Draw(const RendererTime& rendererTime)
	{
	    // Bind the G-Buffer
	    //mGeometryBuffer.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render all opaque geometry to the G-Buffer
		for (RendererComponent* component : mComponents)
		{
			//DrawableComponent* drawableComponent = component->As<DrawableComponent>();
			DrawableComponent* drawableComponent = dynamic_cast<DrawableComponent*>(component);
			if (drawableComponent != nullptr && drawableComponent->Enabled())
			{
				drawableComponent->Draw(rendererTime);
			}
		}

		// Release the G-Buffer
		//mGeometryBuffer.Release();

		// Bind an HDR framebuffer
		// Lights are called here

		// Final pass


	}

	void Renderer::Input(int key, int scanCode, int action, int mod)
	{

	}

	void Renderer::Resize(int width, int height)
	{
        glViewport(0, 0, mScreenWidth, mScreenHeight);
	}

	void Renderer::InitializeWindow()
	{
		//Callback de erro

		if (!glfwInit())
		{
			throw RendererException("glfwInit() failed.");
		}
		#ifdef ALLAN
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        #endif // ALLAN

		mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, mWindowTitle.c_str(), nullptr, nullptr);
		if (mWindow == nullptr)
		{
			glfwTerminate();
			throw RendererException("glfwCreateWindow() failed.");
		}

		glfwMakeContextCurrent(mWindow);
		glfwSwapInterval(1);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			glfwDestroyWindow(mWindow);
			throw RendererException("glewInit() failed.");
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glEnable(GL_FRAMEBUFFER_SRGB);

		///////////////////////////////////////////
		glClearColor(0.1, 0.1, 0.1, 1.0f);

		//Callback de teclas
		glfwSetScrollCallback(mWindow, scrollCallback);
		glfwSetWindowSizeCallback(mWindow, resizeCallback);
		glfwSetKeyCallback(mWindow, KeyboardCallback);
	}

	void Renderer::scrollCallback(GLFWwindow * window, double x, double y)
	{
		if (staticRenderer != nullptr)
		{
			staticRenderer->mMouse->UpdadeWheel(y);
		}
	}

	void Renderer::resizeCallback(GLFWwindow* window, int width, int height)
	{
	    if(staticRenderer)
        {
            staticRenderer->mScreenWidth = width;
            staticRenderer->mScreenHeight = height;
            staticRenderer->Resize(width, height);
        }
	}

	void Renderer::KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mod)
	{
        if(staticRenderer)
        {
            staticRenderer->Input(key, scanCode, action, mod);
        }
	}

	std::string Renderer::GetWindowTitle(int frames)
	{
	    std::stringstream ss;
	    ss << mWindowTitle << " - fps:" << frames << " - " << (1000.0 / (double)frames) << " ms";
	    return ss.str();
	}

}

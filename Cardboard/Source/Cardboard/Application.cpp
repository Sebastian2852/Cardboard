#include "Application.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void glfwErrorCallback(int error, const char* description) {
	CARDBOARD_CRITICAL("GLFW error {0}: {1}", error, description);
}

namespace Cardboard
{

	static Application* s_Application = nullptr;

	Application::Application(ApplicationSpec spec)
		: m_Spec(spec)
	{
		s_Application = this;

		Logger::Init();

		glfwSetErrorCallback(glfwErrorCallback);
		int didInitGlfw = glfwInit();
		CARDBOARD_TRACE("Init GLFW");

		if (!didInitGlfw)
		{
			CARDBOARD_CRITICAL("Failed to init GLFW");
		}

		m_Window = std::make_shared<Window>(spec.WindowWidth, spec.WindowHeight, spec.WindowName);
		m_Window->Create();

		CARDBOARD_TRACE("Application ready");
	}

	Application::~Application()
	{
		CARDBOARD_TRACE("Destroying application");
		s_Application = nullptr;
		m_Window->Destroy();
		glfwTerminate();
		CARDBOARD_TRACE("GLFW terminated");
		CARDBOARD_INFO("Application destroyed");
	}

	void Application::Run()
	{
		float lastTime = 0.0f;
		CARDBOARD_TRACE("Starting application loop");

		while (m_Running)
		{
			// TODO:
			// maybe clean this up to just loop based of should close instead of this
			if (m_Window->ShouldClose())
			{
				m_Running = false;
				break;
			}

			float currentTime = glfwGetTime();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnRender();

			m_Window->Update();
		}
	}

	Application& Application::Get()
	{
		return *s_Application;
	}

}
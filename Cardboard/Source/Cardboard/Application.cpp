#include "Application.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void glfwErrorCallback(int error, const char* description) {
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

namespace Cardboard
{

	static Application* s_Application = nullptr;

	Application::Application(ApplicationSpec spec)
		: m_Spec(spec)
	{
		s_Application = this;

		glfwSetErrorCallback(glfwErrorCallback);
		int didInitGlfw = glfwInit();

		if (!didInitGlfw)
		{
			std::cerr << "Failed to init glfw" << std::endl;
			__debugbreak();
		}

		m_Window = std::make_shared<Window>(spec.WindowWidth, spec.WindowHeight, spec.WindowName);
		m_Window->Create();
	}

	Application::~Application()
	{
		s_Application = nullptr;
		glfwTerminate();
	}

	void Application::Run()
	{
		float lastTime = 0.0f;

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
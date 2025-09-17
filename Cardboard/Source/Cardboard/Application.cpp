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
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Update();
			
			if (m_Window->ShouldClose())
			{
				m_Running = false;
			}
		}
	}

	Application& Application::Get()
	{
		return *s_Application;
	}

}
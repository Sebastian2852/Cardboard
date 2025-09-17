#include "Application.hpp"

#include <iostream>

namespace Cardboard
{

	static Application* s_Application = nullptr;

	Application::Application(ApplicationSpec spec)
		: m_Spec(spec)
	{
		s_Application = this;
	}

	Application::~Application()
	{
		s_Application = nullptr;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			std::cout << "Running..." << std::endl;
		}
	}

	Application& Application::Get()
	{
		return *s_Application;
	}

}
#include "Window.hpp"

#include <iostream>

namespace Cardboard
{

	Window::Window(uint32_t width, uint32_t height, std::string title)
		: m_Width(width), m_Height(height), m_Title(title)
	{}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		m_Handle = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		if (!m_Handle)
		{
			std::cerr << "Failed to create window" << std::endl;
		}

		glfwMakeContextCurrent(m_Handle);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		// VSync by default
		glfwSwapInterval(1);
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(m_Handle);
	}

	void Window::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Handle);
		glfwPollEvents();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Handle) != 0;
	}

}
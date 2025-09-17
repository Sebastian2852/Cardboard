#include "glad/gl.h"
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

		int version = gladLoadGL(glfwGetProcAddress);
		if (version == 0) {
			std::cerr << "Failed to initialize OpenGL context" << std::endl;
			return;
		}
		std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glfwSwapInterval(1); // VSync by default

	}

	void Window::Destroy()
	{
		if (m_Handle)
		{
			glfwDestroyWindow(m_Handle);
			m_Handle = nullptr;
		}
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
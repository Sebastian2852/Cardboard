#include "glad/gl.h"
#include "Window.hpp"
#include "Logger.hpp"

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
			CARDBOARD_ERROR("Failed to create a window");
			return;
		}
		CARDBOARD_TRACE("Created window");

		glfwMakeContextCurrent(m_Handle);

		int version = gladLoadGL(glfwGetProcAddress);
		if (version == 0) {
			CARDBOARD_ERROR("Failed to load GLAD");
			return;
		}
		CARDBOARD_TRACE("Init GLAD");
		CARDBOARD_INFO("Loaded OpenGL v{0}.{1}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glfwSwapInterval(1); // VSync by default

		CARDBOARD_INFO("Created a {0} x {1} window called {2}", m_Width, m_Height, m_Title);
	}

	void Window::Destroy()
	{
		if (m_Handle)
		{
			CARDBOARD_TRACE("Destroying window");
			glfwDestroyWindow(m_Handle);
			m_Handle = nullptr;
			CARDBOARD_INFO("Destroyed window called {0}", m_Title);
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
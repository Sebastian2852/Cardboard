#include "Application.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

#include "Events/WindowEvents.hpp"

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
		CARDBOARD_TRACE("Created window");

		std::string vertexSource = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			out vec3 o_Position;
			out vec3 o_VertexColor;

			void main()
			{
				float x = a_Position.x * 2.0 - 1.0;
				float y = 1.0 - a_Position.y * 2.0;
				float z = a_Position.z;

				vec3 clipPos = vec3(x, y, z);
				gl_Position = vec4(clipPos, 1.0);
				o_Position = clipPos;
				o_VertexColor = a_Color;
			}
		)";


		std::string fragmentSource = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 o_Position;
			in vec3 o_VertexColor;

			void main()
			{
				color = vec4(o_VertexColor, 1.0);
			}
		)";

		m_DefaultShader.reset(new Cardboard::Shader(vertexSource, fragmentSource));
		CARDBOARD_TRACE("Created default shader");

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
			if (m_Window->ShouldClose())
			{
				m_Running = false;
				m_EventBuffer.emplace_back(std::make_unique<WindowCloseEvent>());
			}

			float currentTime = glfwGetTime();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_Window->BeginFrame();

			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			{
				m_DefaultShader->Bind();
				layer->OnRender();
			}

			m_Window->EndFrame();

			for (const std::unique_ptr<BaseEvent>& event : m_EventBuffer)
			{
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				{
					bool handled = layer->OnEvent(*event);
					event->Handled = handled;

					// If this event was handled by this layer we consume it
					// and dont let any layers under it get that event

					// This means that if you have a button and then under it another button
					// the top button can consume the click and the one under it wont get a click
					if (handled)
						break;
				}
			}

			m_EventBuffer.clear();

		}
	}

	Application& Application::Get()
	{
		return *s_Application;
	}

}
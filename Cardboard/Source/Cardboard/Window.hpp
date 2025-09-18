#pragma once

#include <memory>
#include <string>
#include "GLFW/glfw3.h"

namespace Cardboard
{

	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, std::string title);
		~Window();

		void Create();
		void BeginFrame();
		void EndFrame();
		void Destroy();

		bool ShouldClose();
	private:
		uint32_t m_Width, m_Height;
		std::string m_Title;

		GLFWwindow* m_Handle = nullptr;
	};

}
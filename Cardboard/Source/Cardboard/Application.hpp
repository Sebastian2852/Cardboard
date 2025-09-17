#pragma once

#include "Window.hpp"

#include <string>
#include <memory>

namespace Cardboard {

	struct ApplicationSpec
	{
		std::string WindowName;
		uint32_t WindowHeight;
		uint32_t WindowWidth;
	};


	class Application {
	public:
		Application(ApplicationSpec spec);
		~Application();

		void Run();

		static Application& Get();
	private:
		std::shared_ptr<Window> m_Window;
		ApplicationSpec m_Spec;

		bool m_Running = true;
	};
}
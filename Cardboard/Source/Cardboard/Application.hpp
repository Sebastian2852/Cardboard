#pragma once

#include "Window.hpp"
#include "Layer.hpp"

#include <string>
#include <memory>
#include <vector>

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

		template<typename T>
		requires(std::is_base_of_v<Layer, T>)
		void PushLayer()
		{
			m_LayerStack.push_back(std::make_unique<T>());
		}

		static Application& Get();
	private:
		std::shared_ptr<Window> m_Window;
		ApplicationSpec m_Spec;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;

		bool m_Running = true;
	};
}
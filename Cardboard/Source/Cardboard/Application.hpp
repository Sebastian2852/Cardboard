#pragma once

#include "Window.hpp"
#include "Layer.hpp"
#include "Logger.hpp"
#include "Renderer/Shader.hpp"
#include "Events/Event.hpp"

#include <string>
#include <memory>
#include <vector>

namespace Cardboard {

	struct ApplicationSpec
	{
		std::string WindowName = "Cardboard Engine";
		uint32_t WindowHeight = 1280;
		uint32_t WindowWidth = 720;
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
			std::unique_ptr<Layer> newLayer = std::make_unique<T>();
			CARDBOARD_TRACE("New layer pushed to stack: {0}", newLayer->GetDebugName());
			m_LayerStack.push_back(std::move(newLayer));
		}

		static Application& Get();
	private:
		std::shared_ptr<Window> m_Window;
		ApplicationSpec m_Spec;

		std::unique_ptr<Cardboard::Shader> m_DefaultShader;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;
		std::vector<std::unique_ptr<BaseEvent>> m_EventBuffer;

		bool m_Running = true;
	};
}
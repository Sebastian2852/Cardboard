#pragma once

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
		ApplicationSpec m_Spec;

		bool m_Running = true;
	};
}
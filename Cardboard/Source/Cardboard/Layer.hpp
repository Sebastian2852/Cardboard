#pragma once

#include "Application.hpp"
#include "Events/EventBus.hpp"

namespace Cardboard {

	class Layer
	{
	public:
		Layer(std::string name = "UnnamedLayer")
			: m_DebugName(name)
		{}
		virtual ~Layer() = default;

		virtual void OnStart() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}

		const std::string& GetDebugName() const { return m_DebugName; }
	protected:
		std::string m_DebugName = "UnnamedLayer";
		EventBus* m_EventBus = nullptr;
		friend class Application;
	};

}
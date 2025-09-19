#pragma once

#include "Events/Event.hpp"

namespace Cardboard {

	class Layer
	{
	public:
		Layer(std::string name = "UnnamedLayer")
			: m_DebugName(name)
		{}

		virtual ~Layer() = default;

		virtual bool OnEvent(BaseEvent& event) { return false; }
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}

		const std::string& GetDebugName() const { return m_DebugName; }
	protected:
		std::string m_DebugName = "UnnamedLayer";
	};

}
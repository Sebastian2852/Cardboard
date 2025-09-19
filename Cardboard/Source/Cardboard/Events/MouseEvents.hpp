#pragma once

#include <sstream>

#include "Event.hpp"
#include "Util/Keycodes.hpp"

namespace Cardboard
{
	class BaseMouseButtonEvent : public BaseEvent
	{
	public:
		MouseCode GetMouseButton() const { return m_Button; }

	protected:
		BaseMouseButtonEvent(const MouseCode button)
			: m_Button(button)
		{
		}

		MouseCode m_Button;
	};

	///

	class MouseButtonPressedEvent : public BaseMouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: BaseMouseButtonEvent(button)
		{}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button pressed (Button = " << GetMouseButton() << ")";
			return ss.str();
		}

		GENERATE_EVENT_GETTERS(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public BaseMouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: BaseMouseButtonEvent(button)
		{
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button released (Button = " << GetMouseButton() << ")";
			return ss.str();
		}

		GENERATE_EVENT_GETTERS(MouseButtonPressed)
	};
}
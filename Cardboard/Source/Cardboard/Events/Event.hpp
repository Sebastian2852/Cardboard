#pragma once

#include <string>

namespace Cardboard
{

	enum class EventType
	{
		NONE = 0,
		WindowClose, WindowResize, WindowGainFocus, WindowLooseFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

#define GENERATE_EVENT_GETTERS(type) virtual EventType GetType() const override { return EventType::type; }\
											virtual std::string GetName() const override { return #type; }

	class BaseEvent
	{
	public:
		virtual ~BaseEvent() = default;

		bool Handled = false;

		virtual EventType GetType() const = 0;
		virtual std::string GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};
}
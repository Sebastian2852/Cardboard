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

	template<EventType T>
	struct EventTraits;

#define GENERATE_EVENT_GETTERS(enumVal) static EventType GetStaticType() { return EventType::enumVal; } \
										virtual EventType GetType() const override { return GetStaticType(); } \
										virtual std::string GetName() const override { return #enumVal; } \
										friend struct EventTraits<EventType::enumVal>;

#define REGISTER_EVENT_TYPE(className, enumValue) template <> struct EventTraits<EventType::enumValue> { using type = className; }

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
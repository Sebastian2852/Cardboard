#pragma once

#include <string>
#include <sstream>

#include "Event.hpp"
#include "Util/Keycodes.hpp"

namespace Cardboard
{
	class KeycodeEvent : public BaseEvent
	{
	protected:
		KeycodeEvent(KeyCode keycode)
			: m_Keycode(keycode)
		{}

		KeyCode m_Keycode;
	};

	/// 

	class KeyPressedEvent : public KeycodeEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode)
			: KeycodeEvent(keycode)
		{}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key pressed event (Keycode = " << m_Keycode << ")";
			return ss.str();
		}

		GENERATE_EVENT_GETTERS(KeyPressed)
	};

	class KeyReleasedEvent : public KeycodeEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeycodeEvent(keycode)
		{
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key released event (Keycode = " << m_Keycode << ")";
			return ss.str();
		}

		GENERATE_EVENT_GETTERS(KeyReleased)
	};
}
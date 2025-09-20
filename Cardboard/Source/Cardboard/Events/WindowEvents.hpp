#pragma once

#include "Event.hpp"
#include <memory>
#include <string>
#include <sstream>

namespace Cardboard
{
	class WindowCloseEvent : public BaseEvent
	{
	public:
		GENERATE_EVENT_GETTERS(WindowClose)
	};

	class WindowGainFocusEvent : public BaseEvent
	{
	public:
		GENERATE_EVENT_GETTERS(WindowGainFocus)
	};

	REGISTER_EVENT_TYPE(WindowGainFocusEvent, WindowGainFocus);

	class WindowLooseFocusEvent : public BaseEvent
	{
	public:
		GENERATE_EVENT_GETTERS(WindowLooseFocus)
	};

	class WindowResizeEvent : public BaseEvent
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height)
		{}

		uint32_t GetNewWidth() const { return m_Width; }
		uint32_t GetNewHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resize (x = " << GetNewWidth() << " | Y = " << GetNewHeight() << " )";
			return ss.str();
		}

		GENERATE_EVENT_GETTERS(WindowResize)

	private:
		uint32_t m_Width, m_Height;
	};

	class WindowMovedEvent : public BaseEvent
	{
	public:
		WindowMovedEvent(uint32_t xPos, uint32_t yPos)
			: m_XPos(xPos), m_YPos(yPos)
		{
		}

		uint32_t GetNewX() const { return m_XPos; }
		uint32_t GetNewY() const { return m_YPos; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Moved (x = " << GetNewX() << " | Y = " << GetNewY() << " )";
			return ss.str();
		}

		GENERATE_EVENT_GETTERS(WindowMoved)

	private:
		uint32_t m_XPos, m_YPos;
	};
}
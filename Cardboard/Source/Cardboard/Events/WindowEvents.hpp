#pragma once

#include "Event.hpp"
#include <memory>
#include <string>

namespace Cardboard
{
	class WindowCloseEvent : public BaseEvent
	{
	public:
		GENERATE_EVENT_GETTERS(WindowClose)
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
}
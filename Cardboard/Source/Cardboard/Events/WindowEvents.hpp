#pragma once

#include "Event.hpp"

namespace Cardboard
{
	class WindowCloseEvent : public BaseEvent
	{
		GENERATE_EVENT_GETTERS(WindowClose)
	};
}
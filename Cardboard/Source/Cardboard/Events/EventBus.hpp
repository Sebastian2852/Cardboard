#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "Event.hpp"

namespace Cardboard
{
    class EventBus
    {
    public:
        using Callback = std::function<void(const BaseEvent&)>;

        // Connect a callback to an EventType; consumer gets the typed event
        template<EventType T, typename Fn>
        void Connect(Fn&& fn)
        {
            using EventT = typename EventTraits<T>::type;

            // Wrapper lambda converts BaseEvent to concrete type
            auto wrapper = [func = std::forward<Fn>(fn)](const BaseEvent& e)
                {
                    func(static_cast<const EventT&>(e));
                };

            m_Listeners[T].push_back(std::move(wrapper));
        }

        // Dispatch an event to all connected listeners
        void Dispatch(const BaseEvent& e)
        {
            auto it = m_Listeners.find(e.GetType());
            if (it != m_Listeners.end())
            {
                for (auto& cb : it->second)
                    cb(e);
            }
        }

    private:
        std::unordered_map<EventType, std::vector<Callback>> m_Listeners;
    };
}
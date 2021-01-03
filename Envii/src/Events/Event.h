#pragma once
#include <functional>
#include "../Core/Core.h"

namespace Envii
{
	/* Events are blocking for now, must be processed immediately on dispatch
	 * Future revision may buffer the events into a queue for later batch
	 * processing during dedicated portion of frame update.
	 */
	enum class EventType
	{
		None = 0,
		WindowResize, WindowMove, WindowClose, WindowFocus, WindowDefocus,
		AppTick, AppUpdate, AppRender,
		KeyPress, KeyRelease, KeyTyped,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};

	enum EventCategory
	{
		None			= 0,
		Application		= BIT(1),
		Inputs			= BIT(2),
		Keyboard		= BIT(3),
		Mouse			= BIT(4),
		MouseButton		= BIT(5)
	};

#define EVENT_TYPE_IFACE(type) static EventType GetStaticType() { return  EventType::##type; }\
							    virtual EventType GetEventType() const override { return GetStaticType(); }\
							    virtual const char* GetName() const override { return #type; }

#define EVENT_CATEGORY_IFACE(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory cat) { return GetCategoryFlags() & cat; }

		bool m_handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFxn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) 
		: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFxn<T> callback)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_handled = callback(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}
#pragma once

#include "Event.h"

namespace Envii
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		EVENT_TYPE_IFACE(WindowResize)
		EVENT_CATEGORY_IFACE(Application)

		uint32_t GetWidth()  const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: ( " << m_Width << ", " << m_Height << " )";
			return ss.str();
		}

	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE_IFACE(WindowClose)
		EVENT_CATEGORY_IFACE(Application)
	};

	class AppTickEvent : public Event
	{
	public:
		EVENT_TYPE_IFACE(AppTick)
		EVENT_CATEGORY_IFACE(Application)
	};

	class AppUpdateEvent : public Event
	{
	public:
		EVENT_TYPE_IFACE(AppUpdate)
		EVENT_CATEGORY_IFACE(Application)
	};

	class AppRenderEvent : public Event
	{
	public:
		EVENT_TYPE_IFACE(AppRender)
		EVENT_CATEGORY_IFACE(Application)
	};
}



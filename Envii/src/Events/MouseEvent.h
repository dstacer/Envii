#pragma once

#include <sstream>
#include "Event.h"

namespace Envii
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		EVENT_TYPE_IFACE(MouseMove)
		EVENT_CATEGORY_IFACE(Mouse | Inputs)
		float GetMouseX() const { return m_MouseX; }
		float GetMouseY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: ( " << m_MouseX << ", " << m_MouseY << " )";
			return ss.str();
		}

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float amountX, float amountY)
			: m_AmountX(amountX), m_AmountY(amountY) {}
		
		EVENT_TYPE_IFACE(MouseScroll)
		EVENT_CATEGORY_IFACE(Mouse | Inputs)
		float GetAmountX() { return m_AmountX; }
		float GetAmountY() { return m_AmountY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: ( " << m_AmountX << ", " << m_AmountY << " )";
			return ss.str();
		}

	private:
		float m_AmountX;
		float m_AmountY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		EVENT_CATEGORY_IFACE(Inputs | Mouse | MouseButton)
		int GetButton() const { return m_Button; }
	
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_TYPE_IFACE(MouseButtonPress)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << m_Button;
			return ss.str();
		}
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button)
			: MouseButtonEvent(button) {}

		EVENT_TYPE_IFACE(MouseButtonRelease)
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_Button;
			return ss.str();
		}
	};

	
}
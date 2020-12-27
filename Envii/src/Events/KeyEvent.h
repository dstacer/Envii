#pragma once

#include "Event.h"

namespace Envii
{
	class KeyEvent : public Event
	{
	public:
		int GetKeyCode() { return m_KeyCode; }
		
		EVENT_CATEGORY_IFACE(Keyboard | Input);
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " ( " << m_RepeatCount << " repeats )";
			return ss.str();
		}

		EVENT_TYPE_IFACE(KeyPress)
		int GetRepeatCount() const { return m_RepeatCount; }

	protected:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_TYPE_IFACE(KeyReleased)

	};
}

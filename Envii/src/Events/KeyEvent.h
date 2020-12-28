#pragma once

#include "Event.h"

namespace Envii
{
	class KeyEvent : public Event
	{
	public:
		int GetKeyCode() { return m_KeyCode; }
		
		EVENT_CATEGORY_IFACE(Keyboard | Inputs);
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << " ( " << m_RepeatCount << " repeats )";
			return ss.str();
		}

		EVENT_TYPE_IFACE(KeyPress)
		int GetRepeatCount() const { return m_RepeatCount; }

	protected:
		int m_RepeatCount;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_TYPE_IFACE(KeyRelease)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_TYPE_IFACE(KeyTyped)
	};
}

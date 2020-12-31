#pragma once

namespace Envii
{
	class TimeStep
	{
	public:
		TimeStep(float time)
			: m_Time(time) {}

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return m_Time * 1000; }
		operator float() const { return m_Time; }

	private:
		float m_Time = 0.0f;
	};
}
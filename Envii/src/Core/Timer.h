#pragma once

#include <iostream>
#include <chrono>
#include <vector>

namespace Envii
{
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	#define PROFILE_SCOPE(name, resultsVec) Envii::Timer timer##__LINE__(name, [&](Envii::ProfileResult result) { resultsVec.push_back(result); })
	
	template<typename Fn>
	class Timer
	{
	public:
		Timer(const char* name, Fn& func)
			: m_Name(name),
			  m_Stopped(false),
			  m_Func(func)
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			m_Stopped = true;
			m_DurationMics = float(end - start);
			m_Func({ m_Name, m_DurationMics * .001f });
			//std::cout << m_Name << " duration: " << (m_DurationMics * 0.001f) << " ms\n";
		}

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		float m_DurationMics = 0;
		bool m_Stopped;
		Fn m_Func;
	};
}
#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <thread>

namespace Envii
{
	struct ProfileResult
	{
		const char* Name;
		long long Start, End;
		uint32_t Thread;
	};

	struct ProfileSession
	{
		ProfileSession(const std::string& name)
			: m_Name(name) {}
		
		std::string m_Name;
	};

#ifdef EV_DEBUG
	#define EV_PROFILE_BEGIN_SESSION(filepath) Envii::Profiler::Get().BeginSession(filepath)
	#define EV_PROFILE_END_SESSION() Envii::Profiler::Get().EndSession()
	#define EV_PROFILE_SCOPE(name) Envii::ProfileTimer timer##__LINE__(name)
	#define EV_PROFILE_SCOPE_OLD(name, resultsVec) Envii::ProfileTimer timer##__LINE__(name, [&](Envii::ProfileResult result) { resultsVec.push_back(result); })
	#define EV_PROFILE_FUNCTION() EV_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define EV_PROFILE_BEGIN_SESSION(filepath)
	#define EV_PROFILE_END_SESSION()
	#define EV_PROFILE_SCOPE(name) 
	#define EV_PROFILE_SCOPE_OLD(name, resultsVec) 
	#define EV_PROFILE_FUNCTION() 
#endif
	
	class Profiler
	{
	public:
		void BeginSession(const std::string& name)
		{
			std::stringstream ss;
			ss << name << ".json";
			m_OutStream.open(ss.str());
			WriteHeader();
			m_CurrentSession = new ProfileSession(name);
		}

		void EndSession()
		{
			WriteFooter();
			m_OutStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteHeader()
		{
			m_OutStream << "{\"otherData\": {}, \"traceEvents\": [";
			m_OutStream.flush();
		}

		void WriteFooter()
		{
			m_OutStream << "]}";
			m_OutStream.flush();
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutStream << "{";
			m_OutStream << "\"cat\":\"function\",";
			m_OutStream << "\"dur\":" << (result.End - result.Start) << ",";
			m_OutStream << "\"name\":\"" << name << "\",";
			m_OutStream << "\"ph\":\"X\",";
			m_OutStream << "\"pid\":0,";
			m_OutStream << "\"tid\":" << result.Thread << ",";
			m_OutStream << "\"ts\":" << result.Start;
			m_OutStream << "}";

			m_OutStream.flush();
		}

		static Profiler& Get()
		{
			static Profiler* instance = new Profiler();
			return *instance;
		}
	private:
		Profiler()
			: m_CurrentSession(nullptr), m_ProfileCount(0) {}

	private:
		ProfileSession* m_CurrentSession;
		std::ofstream m_OutStream;
		int m_ProfileCount;
	};

	class ProfileTimer
	{
	public:
		ProfileTimer(const char* name)
			: m_Name(name),
			  m_Stopped(false)
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		~ProfileTimer()
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
			uint32_t threadId = (uint32_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
			ProfileResult result = { m_Name, start, end, threadId };
			Profiler::Get().WriteProfile(result);
		}

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		float m_DurationMics = 0;
		bool m_Stopped;
	};
}
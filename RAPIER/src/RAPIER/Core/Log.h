#pragma once

#include "RAPIER/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

//	This ignores warnings in external headers
#pragma warning(push, 0)
	#include "spdlog/spdlog.h"
	#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace RAPIER
{
	class Log
	{
	public:
		static void Init();
		static void Shutdown();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetEditorConsoleLogger() { return s_EditorConsoleLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_EditorConsoleLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}	//	END namespace RAPIER

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::vec2& vec)
{
	return os << '(' << vec.x << ", " << vec.y << ')';
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::vec3& vec)
{
	return os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
}

template<typename OStream>
OStream& operator<<(OStream& os, const glm::vec4& vec)
{
	return os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ')';
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

#ifdef RP_DEBUG	//	DEBUG
	// Core Log Defines
	#define RP_CORE_TRACE(...)		::RAPIER::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define RP_CORE_INFO(...)		::RAPIER::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define RP_CORE_WARN(...)		::RAPIER::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define RP_CORE_ERROR(...)		::RAPIER::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define RP_CORE_CRITICAL(...)	::RAPIER::Log::GetCoreLogger()->critical(__VA_ARGS__)

	//	Editor Console Log defines
	#define RP_CONSOLE_TRACE(...)			::RAPIER::Log::GetEditorConsoleLogger()->trace(__VA_ARGS__)
	#define RP_CONSOLE_INFO(...)			::RAPIER::Log::GetEditorConsoleLogger()->info(__VA_ARGS__)
	#define RP_CONSOLE_WARN(...)			::RAPIER::Log::GetEditorConsoleLogger()->warn(__VA_ARGS__)
	#define RP_CONSOLE_ERROR(...)			::RAPIER::Log::GetEditorConsoleLogger()->error(__VA_ARGS__)
	#define RP_CONSOLE_CRITICAL(...)		::RAPIER::Log::GetEditorConsoleLogger()->critical(__VA_ARGS__)

	//	Client Log Defines
	#define RP_TRACE(...)			::RAPIER::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define RP_INFO(...)			::RAPIER::Log::GetClientLogger()->info(__VA_ARGS__)
	#define RP_WARN(...)			::RAPIER::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define RP_ERROR(...)			::RAPIER::Log::GetClientLogger()->error(__VA_ARGS__)
	#define RP_CRITICAL(...)		::RAPIER::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif

#ifdef RP_RELEASE	//	RFELEASE
	//	Don't Log Engine Messages
	#define RP_CORE_TRACE
	#define RP_CORE_INFO
	#define RP_CORE_WARN
	#define RP_CORE_ERROR
	#define RP_CORE_CRITICAL

	//	Editor Console Log defines
	#define RP_CONSOLE_TRACE(...)			::RAPIER::Log::GetEditorConsoleLogger()->trace(__VA_ARGS__)
	#define RP_CONSOLE_INFO(...)			::RAPIER::Log::GetEditorConsoleLogger()->info(__VA_ARGS__)
	#define RP_CONSOLE_WARN(...)			::RAPIER::Log::GetEditorConsoleLogger()->warn(__VA_ARGS__)
	#define RP_CONSOLE_ERROR(...)			::RAPIER::Log::GetEditorConsoleLogger()->error(__VA_ARGS__)
	#define RP_CONSOLE_CRITICAL(...)		::RAPIER::Log::GetEditorConsoleLogger()->critical(__VA_ARGS__)

	//	Client Log Defines
	#define RP_TRACE(...)			::RAPIER::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define RP_INFO(...)			::RAPIER::Log::GetClientLogger()->info(__VA_ARGS__)
	#define RP_WARN(...)			::RAPIER::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define RP_ERROR(...)			::RAPIER::Log::GetClientLogger()->error(__VA_ARGS__)
	#define RP_CRITICAL(...)		::RAPIER::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif

#ifdef RP_DISTRIBUTION	//	DISTRIBUTION
	//	Don't Log Engine Messages
	#define RP_CORE_TRACE
	#define RP_CORE_INFO
	#define RP_CORE_WARN
	#define RP_CORE_ERROR
	#define RP_CORE_CRITICAL
	//	Don't Log Editor Console Messages
	#define RP_CONSOLE_TRACE(...)
	#define RP_CONSOLE_INFO(...)
	#define RP_CONSOLE_WARN(...)
	#define RP_CONSOLE_ERROR(...)
	#define RP_CONSOLE_CRITICAL(...)
	//	Don't Log Client Messages
	#define RP_TRACE
	#define RP_INFO
	#define RP_WARN
	#define RP_ERROR
	#define RP_CRITICAL
#endif	//	END LOGGING DEFINES

#if !(defined RP_DEBUG || defined RP_RELEASE || defined RP_DISTRIBUTION)
	#error No configuration provided, please define RP_DEBUG, RP_RELEASE, or RP_DISTRIBUTION
#endif

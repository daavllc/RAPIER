/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the definitions for logging in DAGGer
////////////////////////////////
#pragma once

#include "DAGGer/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

//	This ignores warnings in external headers
#pragma warning(push, 0)
	#include "spdlog/spdlog.h"
	#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace DAGGer
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}	//	END namespace DAGGer

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
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

#ifdef Dr_DEBUG	//	DEBUG
	// Core Log Defines
	#define Dr_CORE_TRACE(...)		::DAGGer::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define Dr_CORE_INFO(...)		::DAGGer::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define Dr_CORE_WARN(...)		::DAGGer::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define Dr_CORE_ERROR(...)		::DAGGer::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define Dr_CORE_CRITICAL(...)	::DAGGer::Log::GetCoreLogger()->critical(__VA_ARGS__)

	//	Client Log Defines
	#define Dr_TRACE(...)			::DAGGer::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define Dr_INFO(...)			::DAGGer::Log::GetClientLogger()->info(__VA_ARGS__)
	#define Dr_WARN(...)			::DAGGer::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define Dr_ERROR(...)			::DAGGer::Log::GetClientLogger()->error(__VA_ARGS__)
	#define Dr_CRITICAL(...)		::DAGGer::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif

#ifdef Dr_RELEASE	//	RFELEASE
		//	Don't Log Engine Messages
	#define Dr_CORE_TRACE
	#define Dr_CORE_INFO
	#define Dr_CORE_WARN
	#define Dr_CORE_ERROR
	#define Dr_CORE_CRITICAL
	//	Client Log Defines
	#define Dr_TRACE(...)			::DAGGer::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define Dr_INFO(...)			::DAGGer::Log::GetClientLogger()->info(__VA_ARGS__)
	#define Dr_WARN(...)			::DAGGer::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define Dr_ERROR(...)			::DAGGer::Log::GetClientLogger()->error(__VA_ARGS__)
	#define Dr_CRITICAL(...)		::DAGGer::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif

#ifdef Dr_DISTRIBUTION	//	DISTRIBUTION
		//	Don't Log Engine Messages
	#define Dr_CORE_TRACE
	#define Dr_CORE_INFO
	#define Dr_CORE_WARN
	#define Dr_CORE_ERROR
	#define Dr_CORE_CRITICAL
		//	Don't Log Client Messages
	#define Dr_TRACE
	#define Dr_INFO
	#define Dr_WARN
	#define Dr_ERROR
	#define Dr_CRITICAL
#endif	//	END LOGGING DEFINES

/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the definitions for logging in DAGGer
////////////////////////////////
#pragma once

#include "DAGGer/Core/Base.h"

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

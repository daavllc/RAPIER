#include "drpch.h"
#include "Base.h"

#include "Log.h"

#define DAGGer_BUILD_ID "v0.2.1a"

namespace DAGGer
{
	void InitalizeCore()
	{
		DAGGer::Log::Init();

		Dr_CORE_INFO("DAGGer Engine {}", DAGGer_BUILD_ID);
		Dr_CORE_INFO("Initalizing...");
	}

	void ShutdownCore()
	{
		Dr_CORE_TRACE("Shuting down...");
	}
}

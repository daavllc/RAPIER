#include "drpch.h"
#include "Base.h"

#include "Log.h"

#define DAGGer_BUILD_ID "v0.1.5a"

namespace DAGGer
{
	void InitalizeCore()
	{
		DAGGer::Log::Init();

		Dr_CORE_TRACE("DAGGer Engine {}", DAGGer_BUILD_ID);
		Dr_CORE_TRACE("Initalizing...");
	}

	void ShutdownCore()
	{
		Dr_CORE_TRACE("Shuting down...");
	}
}

#include "drpch.h"
#include "Base.h"

#include "Log.h"

#include "conf/Dr_VER.h"	//	contains DAGGer_BUILD_ID

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

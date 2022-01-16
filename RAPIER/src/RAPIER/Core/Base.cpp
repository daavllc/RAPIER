#include "rppch.h"
#include "Base.h"

#include "Log.h"

#include "conf/RP_VER.h"	//	contains RAPIER_BUILD_ID

namespace RAPIER
{
	void InitalizeCore()
	{
		RAPIER::Log::Init();

		RP_CORE_INFO("RAPIER Engine {}", RAPIER_BUILD_ID);
		RP_CORE_INFO("Initalizing...");
	}

	void ShutdownCore()
	{
		RP_CORE_TRACE("Shuting down...");
	}
}

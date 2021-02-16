/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the entry point for all applications
////////////////////////////
#pragma once
#include "DAGGer/Core/Base.h"

#ifdef Dr_PLATFORM_WINDOWS

extern DAGGer::Application* DAGGer::CreateApplication();

int main(int argc, char** argv)
{
	DAGGer::Log::Init();
	Dr_CORE_INFO("Initalized Log!");
	Dr_TRACE("Initalized Log!");

	Dr_PROFILE_BEGIN_SESSION("Startup", "DAGGerProfile-Startup.json");
	auto app = DAGGer::CreateApplication();
	Dr_PROFILE_END_SESSION();

	Dr_PROFILE_BEGIN_SESSION("Runtime", "DAGGerProfile-Runtime.json");
	app->Run();
	Dr_PROFILE_END_SESSION();

	Dr_PROFILE_BEGIN_SESSION("Shutdown", "DAGGerProfile-Shutdown.json");
	delete app;
	Dr_PROFILE_END_SESSION();
}

#endif
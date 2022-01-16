/////////////////////////////////////////////////////////////////
//	Author: DAAV, LLC (https://github.com/daavofficial)
//  License : MIT
//  Language: C++17
//  This is RAPIER's 'main', and must be included in your project in order to initialize RAPIER
////////////////////////////
#pragma once
#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Application.h"

#ifdef RP_PLATFORM_WINDOWS

extern RAPIER::Application* RAPIER::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	RAPIER::InitalizeCore();

	RP_PROFILE_BEGIN_SESSION("Startup", "RAPIERProfile-Startup.json");
	auto app = RAPIER::CreateApplication({ argc, argv });
	RP_PROFILE_END_SESSION();

	RP_PROFILE_BEGIN_SESSION("Runtime", "RAPIERProfile-Runtime.json");
	app->Run();
	RP_PROFILE_END_SESSION();

	RP_PROFILE_BEGIN_SESSION("Shutdown", "RAPIERProfile-Shutdown.json");
	delete app;
	RAPIER::ShutdownCore();
	RP_PROFILE_END_SESSION();
}

#endif

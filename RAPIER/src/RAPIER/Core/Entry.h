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

	auto app = RAPIER::CreateApplication({ argc, argv });

	app->Run();

	delete app;
	RAPIER::ShutdownCore();
}

#endif

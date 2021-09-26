//------------------------------------------------------------------------------------------------------------
//----====================================================================================================~~~~
//----=                        _______       ___       _____       ______      _____                     =----
//----=                       |  _____|     / _ \     |  __ \     / ____ \    | ____|                    =----
//----=                       | |          / / \ \    | |  \ \   | /    \_\   | |                        =----
//----=                       | |___      | |   | |   | |__/ /   | |   ___    | |__                      =----
//----=                       |  ___|     | |   | |   |  __  |   | |  |_  |   |  __|                     =----
//----=                       | |         | |   | |   | |  | |   | |    | |   | |                        =----
//----=                       | |          \ \_/ /    | |  | |    \ \___| |   | |___                     =----
//----=                       |_|           \___/     |_|  |_|     \_____/    |_____|                    =----
//----=                                                                                                  =----
//----====================================================================================================~~~~
// Author: Anonoei (https://github.com/anonoei)
//	License : GPLv3
//	Language: C++17
//	Dependencies: DAGGer
//	The graphical editor for DAGGer... FORGE - the Fast Open Reliable Graphics Editor!
///////////////////////////////////////
#include <DAGGer.h>				//	Include DAGGer
#include <DAGGer/Core/Entry.h>	//	Entry Point

#include "EditorLayer.h"

#include <string>

#include "conf/Fe_VER.h" // contains FORGE_BUILD_ID

namespace DAGGer
{
	class FORGE : public Application
	{
	public:
		FORGE(ApplicationCommandLineArgs args)
			: Application("DAGGer FORGE", args)
		{
			Dr_INFO("DAGGer FORGE {}", FORGE_BUILD_ID);
			PushLayer(new EditorLayer());
		}

		~FORGE()
		{
		}
	};	//	END class Sandbox

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new FORGE(args);
	}	//	END CreateApplication

}	//	END namespace DAGGer

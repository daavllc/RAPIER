//------------------------------------------------------------------
//----==========================================================----
//----=               __________  ____  ____________           =----
//----=              / ____/ __ \/ __ \/ ____/ ____/           =----
//----=             / /_  / / / / /_/ / / __/ __/              =----
//----=            / __/ / /_/ / _, _/ /_/ / /___              =----
//----=           /_/    \____/_/ |_|\____/_____/              =----
//----=                                                        =----
//----==============================================================
// Author: DAAV, LLC (https://github.com/daavofficial)
//	License : MIT
//	Language: C++17
//	Dependencies: RAPIER
//	The Fast Open Reliable Graphics Editor, RAPIER's graphical editor
///////////////////////////////////////

#include <RAPIER.h>				//	Include RAPIER
#include <RAPIER/Core/Entry.h>	//	Entry Point

#include "EditorLayer.h"

#include <string>

#include "conf/FE_VER.h" // contains FORGE_BUILD_ID

namespace RAPIER
{
	class FORGE : public Application
	{
	public:
		FORGE(const RAPIER::ApplicationSpecification& specification, ApplicationCommandLineArgs args)
			: Application(specification, args)
		{
			RP_INFO("RAPIER FORGE {}", FORGE_BUILD_ID);
			PushLayer(new EditorLayer());
		}

		~FORGE()
		{
		}
	};	//	END class Sandbox

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		RAPIER::ApplicationSpecification specification;
		specification.Name = "FORGE";
		specification.WindowWidth = 1600;
		specification.WindowHeight = 900;
		specification.StartMaximized = true;
		specification.VSync = true;
		specification.Decorations = true;
		specification.EnableImGui = true;


		return new FORGE(specification, args);
	}	//	END CreateApplication

}	//	END namespace RAPIER

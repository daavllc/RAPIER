//------------------------------------------------------------------------------------------------------------
//----====================================================================================================~~~~
//----=                                                                                                  =----
//----=                       MMMMMM       MMMM       MMMM        MMMM       MMMMM                       =----
//----=                       M           M    M      M   M      M           M                           =----
//----=                       M           M    M      M   M      M           M                           =----
//----=                       MMMM        M    M      MMMM       M  MMM      MMMM                        =----
//----=                       M           M    M      M   M      M    M      M                           =----
//----=                       M           M    M      M   M      M    M      M                           =----
//----=                       M            MMMM       M   M       MMMM       MMMMM                       =----
//----=                                                                                                  =----
//----====================================================================================================~~~~
//----=--------------------------------------    version 0.1.2    ---------------------------------------=----
//----====================================================================================================----
// Author: Anonoei (https://github.com/anonoei)
//	License : GPLv3
//	Language: C++17
//	Dependencies: DAGGer
//	The graphical editor for DAGGer... FORGE - the Fast Open Reliable Graphics Editor!
///////////////////////////////////////
#include <DAGGer.h>				//	Include DAGGer
#include <DAGGer/Core/Entry.h>	//	Entry Point

#include "EditorLayer.h"

namespace DAGGer
{
	class FORGE : public Application
	{
	public:
		FORGE(ApplicationCommandLineArgs args)
			: Application("DAGGer FORGE", args)
		{
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

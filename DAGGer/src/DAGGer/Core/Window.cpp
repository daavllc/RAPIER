/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation for creating a Window
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Core/Window.h"

#ifdef Dr_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace DAGGer
{
	Scope<Window> Window::Create(const WindowSpecification& specification)
	{
		#ifdef Dr_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(specification);
		#else
			Dr_CORE_ASSERT(false, "Unknown platform!");
			return nullptr
		#endif
	}

}	//	END namespace DAGGer

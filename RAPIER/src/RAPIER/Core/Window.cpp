#include "rppch.h"
#include "RAPIER/Core/Window.h"

#ifdef RP_PLATFORM_WINDOWS
	#include "RAPIER/Platform/Windows/WindowsWindow.h"
#endif

namespace RAPIER
{
	Scope<Window> Window::Create(const WindowSpecification& specification)
	{
		#ifdef RP_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(specification);
		#else
			RP_CORE_ASSERT(false, "Unknown platform!");
			return nullptr
		#endif
	}

}	//	END namespace RAPIER

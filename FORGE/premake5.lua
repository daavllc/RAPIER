project "FORGE"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.h",
		"src/**.cpp",
		
		"%{IncludeDir.Config}/conf/FE_VER.h"
	}
	
	includedirs
	{
		"%{wks.location}/RAPIER/vendor/spdlog/include",
		"%{wks.location}/RAPIER/src",
		"%{wks.location}/RAPIER/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.DAALS}",

		"%{IncludeDir.Config}",
		"%{wks.location}"
	}
	
	links
	{
		"RAPIER"
	}
		
	filter {"system:windows"}			--	WINDOWS
		systemversion "latest"

	filter {"system:linux"}				--	LINUX
		systemversion "latest"

	filter {"system:macosx"}			--	MACOS
		systemversion "latest"

	filter "configurations:Debug"	--	DEBUG
		defines "RP_DEBUG"
		runtime "Debug"
		symbols "on"

		postbuildcommands
		{
			'{COPYDIR} "%{LibraryDir.VulkanSDK_DebugDLL}" "%{cfg.targetdir}"',
			'{COPY} "../RAPIER/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"	--	RELEASE
		defines "RP_RELEASE"
		runtime "Release"
		optimize "on"

		postbuildcommands
		{
			'{COPY} "../RAPIER/vendor/mono/bin/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		defines "RP_DISTRIBUTION"
		runtime "Release"
		optimize "on"

		postbuildcommands
		{
			'{COPY} "../RAPIER/vendor/mono/bin/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

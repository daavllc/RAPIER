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
		
		"%{IncludeDir.Config}/conf/Fe_VER.h"
	}
	
	includedirs
	{
		"%{wks.location}/DAGGer/vendor/spdlog/include",
		"%{wks.location}/DAGGer/src",
		"%{wks.location}/DAGGer/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.DAALS}",

		"%{IncludeDir.Config}",
		"%{wks.location}"
	}
	
	links
	{
		"DAGGer"
	}
		
	filter {"system:windows"}			--	WINDOWS
		systemversion "latest"

	filter {"system:linux"}				--	LINUX
		systemversion "latest"

	filter {"system:macosx"}			--	MACOS
		systemversion "latest"

	filter "configurations:Debug"	--	DEBUG
		defines "Dr_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"	--	RELEASE
		defines "Dr_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		defines "Dr_DISTRIBUTION"
		runtime "Release"
		optimize "on"

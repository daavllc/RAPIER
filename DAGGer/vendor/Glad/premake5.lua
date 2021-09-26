project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"include/glad.h",
			"include/KHR/khrplatform.h",
			"src/glad.c",
		}
		includedirs
		{
			"include"
		}	

	filter "system:windows"			--	WINDOWS
		systemversion "latest"

	filter "configurations:Debug"	--	DEBUG
		runtime "Debug"
		symbols "on"		
		
	filter "configurations:Release"	--	RELEASE
		runtime "Release"
		optimize "on"
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		runtime "Release"
		optimize "on"

project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"OpenGL/include/glad.h",
			"OpenGL/include/KHR/khrplatform.h",
			"OpenGL/src/glad.c",

			"Vulkan/include/**.h",
			"Vulkan/src/vulkan.c"
		}
		includedirs
		{
			"Vulkan/include",
			"OpenGL/include"
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
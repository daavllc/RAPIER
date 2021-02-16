project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{wks.location}/DAGGer/vendor/",
		"%{wks.location}/DAGGer/src",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.entt}"
	}
	
	links
	{
		"DAGGer"
	}
		
	filter "system:windows"			--	WINDOWS
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
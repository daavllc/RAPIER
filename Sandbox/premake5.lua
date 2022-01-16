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
		"%{wks.location}/RAPIER/vendor/",
		"%{wks.location}/RAPIER/src",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.entt}"
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
		defines "RPDEBUG"
		runtime "Debug"
		symbols "on"		
		
	filter "configurations:Release"	--	RELEASE
		defines "RPRELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		defines "RPDISTRIBUTION"
		runtime "Release"
		optimize "on"

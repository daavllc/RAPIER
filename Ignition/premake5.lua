project "Ignition"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{wks.location}/RAPIER/src",
        "%{wks.location}/RAPIER/vendor",
        "%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
        "%{IncludeDir.Glad}",
		"%{IncludeDir.miniaudio}"
    }

    links
    {
        "RAPIER"
    }

    filter {"system:windows"}			--	WINDOWS
		systemversion "latest"

		defines
		{
			"RP_COMPILE_WINDOWS"
		}

	filter {"system:linux"}				--	LINUX
		systemversion "latest"

		defines
		{
			"RP_COMPILE_LINUX"
		}

	filter {"system:macosx"}			--	MACOS
		systemversion "latest"

		defines
		{
			"RP_COMPILE_MACOS"
		}


        filter "configurations:Debug"	--	DEBUG
		defines
        {
            "RP_DEBUG", 
            "RP_OUTPUT=bin/%{outputdir}"
        }
		runtime "Debug"
		symbols "on"

		postbuildcommands
		{
			--'{COPYDIR} "%{LibraryDir.VulkanSDK_DebugDLL}" "%{cfg.targetdir}"',
			'{COPY} "%{wks.location}/RAPIER/vendor/mono/bin/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"	--	RELEASE
        defines
        {
            "RP_RELEASE", 
            "RP_OUTPUT=bin/%{outputdir}"
        }
		runtime "Release"
		optimize "on"

		postbuildcommands
		{
			'{COPY} "%{wks.location}/RAPIER/vendor/mono/bin/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}
		
	filter "configurations:Distribution"	--	DISTRIBUTION
        defines
        {
            "RP_DISTRIBUTION", 
            "RP_OUTPUT=\"bin/%{outputdir}\""
        }
		runtime "Release"
		optimize "on"

		postbuildcommands
		{
			'{COPY} "%{wks.location}/RAPIER/vendor/mono/bin/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
		}

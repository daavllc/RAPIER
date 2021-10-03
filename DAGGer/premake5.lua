project "DAGGer"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "drpch.h"
	pchsource "src/drpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"%{IncludeDir.stb_image}/**.h",
		"%{IncludeDir.stb_image}/**.cpp",

		"%{IncludeDir.glm}/**.hpp",
		"%{IncludeDir.glm}/**.inl",
		
		"%{IncludeDir.ImGuizmo}/**.h",
		"%{IncludeDir.ImGuizmo}/**.cpp",
		
		"%{IncludeDir.Config}/conf/Dr_VER.h"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",	--	For ImGui
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor",
		"vendor/spdlog/include",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.choc}",

		"%{IncludeDir.Config}",
		"%{wks.location}"
	}

	links
	{
		"Box2D",
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}
	
	filter "files:vendor/ImGuizmo/**.cpp"
		flags {"NoPCH"}

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

		links
		{
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}
		
	filter "configurations:Release"	--	RELEASE
		defines "Dr_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		defines "Dr_DISTRIBUTION"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

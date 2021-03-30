project "DAGGer"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "drpch.h"
	pchsource "src/drpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.cpp",
		"vendor/stb_image/**.h",

		"vendor/glm/**.hpp",
		"vendor/glm/**.inl",
		
		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Glad}/Vulkan/include",
		"%{IncludeDir.Glad}/OpenGL/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.mono}",
		"%{wks.location}",

		"%{IncludeDir.Vulkan}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"%{LibraryDir.mono}"
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
		
	filter "configurations:Release"	--	RELEASE
		defines "Dr_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Distribution"	--	DISTRIBUTION
		defines "Dr_DISTRIBUTION"
		runtime "Release"
		optimize "on"

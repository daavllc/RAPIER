workspace "DAGGer"
	architecture "x64"
	startproject "FORGE"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"]		= "DAGGer/vendor/GLFW/include"
IncludeDir["Glad"]		= "DAGGer/vendor/Glad"
IncludeDir["ImGui"]		= "DAGGer/vendor/ImGui"
IncludeDir["glm"]		= "DAGGer/vendor/glm"
IncludeDir["stb_image"] = "DAGGer/vendor/stb_image"
IncludeDir["entt"]		= "DAGGer/vendor/entt/include"
IncludeDir["yaml_cpp"]  = "DAGGer/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"]  = "DAGGer/vendor/ImGuizmo"

IncludeDir["Vulkan"]	= "C:/VulkanSDK/1.2.162.1/Include"

group "Dependencies"
	include "DAGGer/vendor/GLFW"
	include "DAGGer/vendor/Glad"
	include "DAGGer/vendor/ImGui"
	include "DAGGer/vendor/yaml-cpp"

group ""

project "DAGGer"
	location "DAGGer"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "drpch.h"
	pchsource "DAGGer/src/drpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",

		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl",
		
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",	--	For ImGui
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}/Vulkan/include",
		"%{IncludeDir.Glad}/OpenGL/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",


		"%{IncludeDir.Vulkan}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp"
	}
	
	filter "files:DAGGer/vendor/ImGuizmo/**.cpp"
		flags {"NoPCH"}

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

		-- Begin Project Sandbox ------------------------------------------------------------
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"DAGGer/vendor/",
		"DAGGer/src",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.Glad}/Vulkan/include",
		"%{IncludeDir.Glad}/OpenGL/include",
		"%{IncludeDir.entt}",
		"%{IncludeDir.Vulkan}"
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


		-- Begin Project FORGE ------------------------------------------------------------
project "FORGE"
	location "FORGE"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"DAGGer/vendor/",
		"DAGGer/src",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.Glad}/Vulkan/include",
		"%{IncludeDir.Glad}/OpenGL/include",
		"%{IncludeDir.entt}",
		"%{IncludeDir.Vulkan}"
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
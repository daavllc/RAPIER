include "./vendor/premake/premake_customization/solution_items.lua"

workspace "DAGGer"
	startproject "FORGE"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}
	
	platforms
	{
		"Win-64",
		"Win-32",
		"Linux-64",
		"Linux-32",
		"MacOS-64",
		"MacOS-32",
		"iOS-ARM",
		"Anrdoid-ARM",
	}

	filter {"platforms:Win-64 or Linux-64 or MacOS-64"}		--	x86_64
		architecture "x86_64"

	filter {"platforms:Win-32 or Linux-32 or MacOS-32"}		--	x86
		architecture "x86"

	filter {"platforms:iOS-64 or Android-64"}				--	ARM
		architecture "ARM"

	filter {"system:windows"}			--	WINDOWS
		removeplatforms { "Linux-32", "Linux-64", "MacOS-32", "MacOS-64" }

	filter {"system:linux"}				--	LINUX
		removeplatforms { "Win-32", "Win-64", "MacOS-32", "MacOS-64" }

	filter {"system:macosx"}			--	MACOS
		removeplatforms { "Linux-32", "Linux-64", "Win-32", "Win-64" }

	filter ""

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"]		= "%{wks.location}/DAGGer/vendor/glfw/include"
IncludeDir["Glad"]		= "%{wks.location}/DAGGer/vendor/Glad"
IncludeDir["ImGui"]		= "%{wks.location}/DAGGer/vendor/imgui"
IncludeDir["glm"]		= "%{wks.location}/DAGGer/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/DAGGer/vendor/stb_image"
IncludeDir["entt"]		= "%{wks.location}/DAGGer/vendor/entt/include"
IncludeDir["yaml_cpp"]  = "%{wks.location}/DAGGer/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"]  = "%{wks.location}/DAGGer/vendor/ImGuizmo"

IncludeDir["Vulkan"]	= "C:/VulkanSDK/1.2.162.1/Include"

group "Dependencies"
	include "vendor/premake"
	include "DAGGer/vendor/glfw"
	include "DAGGer/vendor/Glad"
	include "DAGGer/vendor/imgui"
	include "DAGGer/vendor/yaml-cpp"

group ""

include "DAGGer"
include "FORGE"
include "Sandbox"

include "./vendor/premake/premake_customization/solution_items.lua"

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
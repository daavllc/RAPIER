include "./vendor/premake/premake_customization/solution_items.lua"
include "dependencies.lua"

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

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	filter {"platforms:Win-64 or Linux-64 or MacOS-64"}		--	x86_64
		architecture "x86_64"

	filter {"platforms:Win-32 or Linux-32 or MacOS-32"}		--	x86
		architecture "x86"

	filter {"platforms:iOS-64 or Android-64"}				--	ARM
		architecture "ARM"

	filter {"system:windows"}			--	WINDOWS
		removeplatforms { "Linux-32", "Linux-64", "MacOS-32", "MacOS-64" }
		defaultplatform "Win-64"

	filter {"system:linux"}				--	LINUX
		removeplatforms { "Win-32", "Win-64", "MacOS-32", "MacOS-64" }
		defaultplatform "Linux-64"

	filter {"system:macosx"}			--	MACOS
		removeplatforms { "Linux-32", "Linux-64", "Win-32", "Win-64" }
		defaultplatform "MacOS-64"
	filter ""

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.platform}"

group "Dependencies"
	include "vendor/premake"
	include "DAGGer/vendor/glfw"
	include "DAGGer/vendor/Glad"
	include "DAGGer/vendor/imgui"
	include "DAGGer/vendor/yaml-cpp"
group ""

group "Core"
	include "DAGGer"
group ""

group "Tools"
	include "FORGE"
group ""

group "Sandbox"
	include "Sandbox"
group ""

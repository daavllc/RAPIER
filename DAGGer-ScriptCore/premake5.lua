project "DAGGer-ScriptCore"
	kind "SharedLib"
	language "C#"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{wks.location}/%{prj.name}/src/**.cs", 
	}

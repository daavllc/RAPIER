
include "./config/dependencies.lua"

	
	group "Dependencies"
		include "vendor/premake"
		include "DAGGer/vendor/box2d"
		include "DAGGer/vendor/glfw"
		include "DAGGer/vendor/Glad"
		include "DAGGer/vendor/imgui"
		include "DAGGer/vendor/yaml-cpp"
	group ""
	
	group "Core"
		include "DAGGer"
	group ""

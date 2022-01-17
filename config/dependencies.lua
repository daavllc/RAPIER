
-- RAPIER Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"]   = "%{wks.location}/RAPIER/vendor/stb_image"
IncludeDir["yaml_cpp"]    = "%{wks.location}/RAPIER/vendor/yaml-cpp/include"
IncludeDir["Box2D"]       = "%{wks.location}/RAPIER/vendor/box2d/include"
IncludeDir["GLFW"]        = "%{wks.location}/RAPIER/vendor/glfw/include"
IncludeDir["Glad"]        = "%{wks.location}/RAPIER/vendor/Glad/include"
IncludeDir["ImGui"]       = "%{wks.location}/RAPIER/vendor/imgui"
IncludeDir["ImGuizmo"]    = "%{wks.location}/RAPIER/vendor/ImGuizmo"
IncludeDir["glm"]         = "%{wks.location}/RAPIER/vendor/glm/include"
IncludeDir["entt"]        = "%{wks.location}/RAPIER/vendor/entt/include"
IncludeDir["shaderc"]     = "%{wks.location}/RAPIER/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/RAPIER/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"]   = "%{VULKAN_SDK}/Include"
IncludeDir["choc"]        = "%{wks.location}/RAPIER/vendor/choc"
IncludeDir["mono"]        = "%{wks.location}/RAPIER/vendor/mono/include"
IncludeDir["miniaudio"]   = "%{wks.location}/RAPIER/vendor/miniaudio/include"
IncludeDir["optick"]   = "%{wks.location}/RAPIER/vendor/optick/src"

IncludeDir["Config"]      = "%{wks.location}/config/include"
IncludeDir["DAALS"]       = "%{wks.location}/RAPIER/vendor/DAALS/include"

LibraryDir = {}

LibraryDir["VulkanSDK"]          = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"]    = "%{wks.location}/RAPIER/vendor/VulkanSDK/lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/RAPIER/vendor/VulkanSDK/Bin"

Library = {}
Library["Vulkan"]                   = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"]              = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"]            = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"]        = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"]   = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"]        = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"]          = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"]      = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

Library["mono"]                     = "%{wks.location}/RAPIER/vendor/mono/lib/Release/mono-2.0-sgen.lib"

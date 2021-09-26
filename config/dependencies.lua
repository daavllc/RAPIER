
-- DAGGer Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"]   = "%{wks.location}/DAGGer/vendor/stb_image"
IncludeDir["yaml_cpp"]    = "%{wks.location}/DAGGer/vendor/yaml-cpp/include"
IncludeDir["Box2D"]       = "%{wks.location}/DAGGer/vendor/box2d/include"
IncludeDir["GLFW"]        = "%{wks.location}/DAGGer/vendor/glfw/include"
IncludeDir["Glad"]        = "%{wks.location}/DAGGer/vendor/Glad/include"
IncludeDir["ImGui"]       = "%{wks.location}/DAGGer/vendor/imgui"
IncludeDir["ImGuizmo"]    = "%{wks.location}/DAGGer/vendor/ImGuizmo"
IncludeDir["glm"]         = "%{wks.location}/DAGGer/vendor/glm/include"
IncludeDir["entt"]        = "%{wks.location}/DAGGer/vendor/entt/include"
IncludeDir["shaderc"]     = "%{wks.location}/DAGGer/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/DAGGer/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"]   = "%{VULKAN_SDK}/Include"

IncludeDir["Config"]      = "%{wks.location}/config/include"
IncludeDir["DAALS"]       = "%{wks.location}/DAGGer/vendor/DAALS/include"

LibraryDir = {}

LibraryDir["VulkanSDK"]          = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"]    = "%{wks.location}/DAGGer/vendor/VulkanSDK/lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/DAGGer/vendor/VulkanSDK/Bin"

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

#include "drpch.h"
#include "VulkanContext.h"

namespace DAGGer
{

	VulkanContext::VulkanContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
        Dr_CORE_ASSERT(windowHandle, "Window handle is null");
        Dr_CORE_ASSERT(!glfwVulkanSupported(), "GLFW doesn't support Vulkan!");
	}

	void VulkanContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadVulkan(nullptr, nullptr);
        Dr_CORE_ASSERT(status, "Failed to intialize Glad!");

        uint32_t extensions_count = 0;
        const char** extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
        createInstance(extensions, extensions_count);
        Dr_CORE_INFO("Created Vulkan Instance!");
        pickPhysicalDevice();
        Dr_CORE_INFO("Picked physical device!");
        createLogicalDevice();
        Dr_CORE_INFO("Created Vulkan Device!");
        createDescriptorPool();
        Dr_CORE_INFO("Created Descriptor pool!");
	}

	void VulkanContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}




	// Private functions
    static void checkVkResult(VkResult err)
    {
        if (err == 0)
            return;
        Dr_CORE_ERROR("[Vulkan] Error: {0}'", err);
        if (err < 0)
            abort();
    }

#ifdef Dr_DEBUG

#endif // VULKAN DEBUG REPORT
	void VulkanContext::createInstance(const char** extensions, uint32_t extensions_count)
	{
        VkResult err;
        VkInstanceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.enabledExtensionCount = extensions_count;
		create_info.ppEnabledExtensionNames = extensions;
        #if 0
            // Enabling validation layers
            const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
            create_info.enabledLayerCount = 1;
            create_info.ppEnabledLayerNames = layers;

            // Enable debug report extension (we need additional storage, so we duplicate the user array to add our new extension to it)
            const char** extensions_ext = (const char**)malloc(sizeof(const char*) * (extensions_count + 1));
            memcpy(extensions_ext, extensions, extensions_count * sizeof(const char*));
            extensions_ext[extensions_count] = "VK_EXT_debug_report";
            create_info.enabledExtensionCount = extensions_count + 1;
            create_info.ppEnabledExtensionNames = extensions_ext;

            // Create Vulkan Instance
            err = vkCreateInstance(&create_info, storage.Allocator, &storage.Instance);
            checkVkResult(err);
            free(extensions_ext);

            // Get the function pointer (required for any extensions)
            auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(storage.Instance, "vkCreateDebugReportCallbackEXT");
            Dr_CORE_ASSERT(vkCreateDebugReportCallbackEXT != NULL);

            // Setup the debug report callback
            VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
            debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
            debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
            debug_report_ci.pfnCallback = debug_report;
            debug_report_ci.pUserData = NULL;
            err = vkCreateDebugReportCallbackEXT(g_Instance, &debug_report_ci, g_Allocator, &g_DebugReport);
            check_vk_result(err);
        #else
            // Create Vulkan Instance without any debug feature
            err = vkCreateInstance(&create_info, storage.Allocator, &storage.Instance);
            checkVkResult(err);
            //IM_UNUSED(g_DebugReport);
        #endif
	}

    void VulkanContext::pickPhysicalDevice()
    {
        VkResult err;
        uint32_t gpu_count;
        err = vkEnumeratePhysicalDevices(storage.Instance, &gpu_count, NULL);
        checkVkResult(err);
        Dr_CORE_ASSERT(gpu_count > 0, "No GPU found!");

        VkPhysicalDevice* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
        err = vkEnumeratePhysicalDevices(storage.Instance, &gpu_count, gpus);
        checkVkResult(err);

        // If a number >1 of GPUs got reported, you should find the best fit GPU for your purpose
        // e.g. VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU if available, or with the greatest memory available, etc.
        // for sake of simplicity we'll just take the first one, assuming it has a graphics queue family.
        storage.PhysicalDevice = gpus[0];
        free(gpus);

        // Select Graphics QUEUE family

        uint32_t count;
        vkGetPhysicalDeviceQueueFamilyProperties(storage.PhysicalDevice, &count, NULL);
        VkQueueFamilyProperties* queues = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * count);
        vkGetPhysicalDeviceQueueFamilyProperties(storage.PhysicalDevice, &count, queues);
        for (uint32_t i = 0; i < count; i++)
            if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                storage.QueueFamily = i;
                break;
            }
        free(queues);
        Dr_CORE_ASSERT(g_QueueFamily != (uint32_t)-1);
    }

    void VulkanContext::createLogicalDevice()   //  w/ 1 queue
    {
        int device_extension_count = 1;
        const char* device_extensions[] = { "VK_KHR_swapchain" };
        const float queue_priority[] = { 1.0f };
        VkDeviceQueueCreateInfo queue_info[1] = {};
        queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_info[0].queueFamilyIndex = storage.QueueFamily;
        queue_info[0].queueCount = 1;
        queue_info[0].pQueuePriorities = queue_priority;
        VkDeviceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
        create_info.pQueueCreateInfos = queue_info;
        create_info.enabledExtensionCount = device_extension_count;
        create_info.ppEnabledExtensionNames = device_extensions;
        VkResult err = vkCreateDevice(storage.PhysicalDevice, &create_info, storage.Allocator, &storage.Device);
        checkVkResult(err);
        vkGetDeviceQueue(storage.Device, storage.QueueFamily, 0, &storage.Queue);
    }

    void VulkanContext::createDescriptorPool()
    {
        VkDescriptorPoolSize pool_sizes[] =
        {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };
        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * sizeof(pool_sizes);
        pool_info.poolSizeCount = (uint32_t)sizeof(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        VkResult err = vkCreateDescriptorPool(storage.Device, &pool_info, storage.Allocator, &storage.DescriptorPool);
        checkVkResult(err);
    }
}	//	END namespace DAGGer
#pragma once
#include "DAGGer/Renderer/GraphicsContext.h"

#include <glad/Vulkan/include/glad/vulkan.h>

//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/src/internal.h>

struct GLFWwindow;

namespace DAGGer
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		void createInstance(const char** extensions, uint32_t extensions_count);
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createDescriptorPool();

		void setupDebugMessenger();
	private:
		GLFWwindow* m_WindowHandle;
		struct VkStorage
		{
			static VkAllocationCallbacks*	Allocator;
			static VkInstance				Instance;
			static VkPhysicalDevice			PhysicalDevice;
			static VkDevice					Device;
			static uint32_t					QueueFamily;
			static VkQueue					Queue;
			static VkPipelineCache			PipelineCache;
			static VkDescriptorPool			DescriptorPool;
			static VkSurfaceKHR				surface;
		};
		
		VkStorage storage;
	};

}	//	END namespace DAGGer
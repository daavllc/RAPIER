#include "rppch.h"
#include "RAPIER/Renderer/GraphicsContext.h"

#include "RAPIER/Renderer/Renderer.h"

#include "RAPIER/Platform/OpenGL/OpenGlContext.h"
//#include "RAPIER/Platform/Vulkan/VulkanContext.h"

namespace RAPIER
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		RP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			//case RendererAPI::API::Vulkan:		return CreateScope<VulkanContext>(static_cast<GLFWwindow*>(window));
		}

		RP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}	//	END namespace RAPIER

/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation of GraphicsContexts
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Renderer/GraphicsContext.h"

#include "DAGGer/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGlContext.h"
//#include "Platform/Vulkan/VulkanContext.h"

namespace DAGGer
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		Dr_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
			//case RendererAPI::API::Vulkan:		return CreateScope<VulkanContext>(static_cast<GLFWwindow*>(window));
		}

		Dr_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}	//	END namespace DAGGer

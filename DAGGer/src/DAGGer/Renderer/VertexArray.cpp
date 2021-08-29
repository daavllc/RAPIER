/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation of VertexArrays
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Renderer/VertexArray.h"

#include "DAGGer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace DAGGer
{
	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLVertexArray>::Create();
			case RendererAPI::API::Vulkan:		Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}	//	END namespace DAGGer

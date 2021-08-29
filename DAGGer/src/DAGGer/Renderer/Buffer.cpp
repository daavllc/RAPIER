/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation for Vertex and Index buffers
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Renderer/Buffer.h"

#include "DAGGer/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace DAGGer
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(size);
			case RendererAPI::API::Vulkan:	Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		//	What API are we using?
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(vertices, size);
			case RendererAPI::API::Vulkan:	Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		//	What API are we using?
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(indices, size);
			case RendererAPI::API::Vulkan:	Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}



}	//	END namespace DAGGEr

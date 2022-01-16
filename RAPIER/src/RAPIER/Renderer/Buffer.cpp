#include "rppch.h"
#include "RAPIER/Renderer/Buffer.h"

#include "RAPIER/Renderer/Renderer.h"

#include "RAPIER/Platform/OpenGL/OpenGLBuffer.h"

namespace RAPIER
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(size);
			case RendererAPI::API::Vulkan:	RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		//	What API are we using?
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLVertexBuffer>::Create(vertices, size);
			case RendererAPI::API::Vulkan:	RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		//	What API are we using?
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLIndexBuffer>::Create(indices, size);
			case RendererAPI::API::Vulkan:	RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}



}	//	END namespace DAGGEr

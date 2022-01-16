#include "rppch.h"
#include "RAPIER/Renderer/VertexArray.h"

#include "RAPIER/Renderer/Renderer.h"
#include "RAPIER/Platform/OpenGL/OpenGLVertexArray.h"

namespace RAPIER
{
	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLVertexArray>::Create();
			case RendererAPI::API::Vulkan:		RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}	//	END namespace RAPIER

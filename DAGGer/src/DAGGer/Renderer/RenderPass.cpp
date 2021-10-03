#include "drpch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLRenderPass.h"

namespace DAGGer
{
	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    Dr_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return Ref<OpenGLRenderPass>::Create(spec);
		}

		Dr_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}	//	END namespace DAGGer

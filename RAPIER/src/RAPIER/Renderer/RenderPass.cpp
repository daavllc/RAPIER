#include "rppch.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "RAPIER/Platform/OpenGL/OpenGLRenderPass.h"

namespace RAPIER
{
	Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    RP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return Ref<OpenGLRenderPass>::Create(spec);
		}

		RP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}	//	END namespace RAPIER

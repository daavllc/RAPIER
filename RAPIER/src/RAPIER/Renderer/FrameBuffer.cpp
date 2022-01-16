#include "rppch.h"
#include "FrameBuffer.h"

#include "RAPIER/Renderer/Renderer.h"

#include "RAPIER/Platform/OpenGL/OpenGLFrameBuffer.h"

namespace RAPIER
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:	return Ref<OpenGLFrameBuffer>::Create(spec);
			case RendererAPI::API::Vulkan:	RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}	//	END namespace RAPIER

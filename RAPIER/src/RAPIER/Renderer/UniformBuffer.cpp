#include "rppch.h"
#include "UniformBuffer.h"

#include "RAPIER/Renderer/Renderer.h"
#include "RAPIER/Platform/OpenGL/OpenGLUniformBuffer.h"

namespace RAPIER
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return Ref<OpenGLUniformBuffer>::Create(size, binding);
		}

		RP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

#include "drpch.h"
#include "UniformBuffer.h"

#include "DAGGer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace DAGGer
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    Dr_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return Ref<OpenGLUniformBuffer>::Create(size, binding);
		}

		Dr_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}

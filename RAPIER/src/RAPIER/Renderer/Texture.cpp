#include "rppch.h"
#include "RAPIER/Renderer/Texture.h"

#include "RAPIER/Renderer/Renderer.h"
#include "RAPIER/Platform/OpenGL/OpenGLTexture.h"

namespace RAPIER
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLTexture2D>::Create(width, height);
			case RendererAPI::API::Vulkan:		RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLTexture2D>::Create(path);
			case RendererAPI::API::Vulkan:		RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}	//	END namespace RAPIER

/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation for textures
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Renderer/Texture.h"

#include "DAGGer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace DAGGer
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLTexture2D>::Create(width, height);
			case RendererAPI::API::Vulkan:		Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLTexture2D>::Create(path);
			case RendererAPI::API::Vulkan:		Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

}	//	END namespace DAGGer

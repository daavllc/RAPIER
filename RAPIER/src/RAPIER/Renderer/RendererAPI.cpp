#include "rppch.h"
#include "RendererAPI.h"

#include "RAPIER/Platform/OpenGL/OpenGLRendererAPI.h"

namespace RAPIER
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    RP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		case RendererAPI::API::Vulkan:    RP_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}	//	END namespace RAPIER

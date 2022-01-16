#include "rppch.h"
#include "RenderCommand.h"

#include "RAPIER/Platform/OpenGL/OpenGLRendererAPI.h"

namespace RAPIER
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}	//	END namespace RAPIER
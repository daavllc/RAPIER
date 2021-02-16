/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation of low-end render commands
////////////////////////////////
#include "drpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace DAGGer
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}	//	END namespace DAGGer
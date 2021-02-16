//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the OpenGL definitions for the GraphicsContext.h file
#pragma once
#include "DAGGer/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace DAGGer
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}	//	END namespace DAGGer
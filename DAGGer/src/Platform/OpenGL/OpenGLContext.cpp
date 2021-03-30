//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the implementation for the GraphicsContext.cpp file
#include "drpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/OpenGL/include/glad/glad.h>
#include <GLFW/glfw3.h>

namespace DAGGer
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		Dr_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		Dr_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		Dr_CORE_ASSERT(status, "Failed to intialize Glad!")

		Dr_CORE_INFO("OpenGL Info: ");
		Dr_CORE_INFO("    Vendor: {0}",   glGetString(GL_VENDOR));
		Dr_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		Dr_CORE_INFO("    Version: {0}",  glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		Dr_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}	//	END namespace DAGGer

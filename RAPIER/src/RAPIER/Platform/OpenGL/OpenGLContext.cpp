#include "rppch.h"
#include "RAPIER/Platform/OpenGL/OpenGLContext.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

namespace RAPIER
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		RP_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		RP_PROFILE_FUNC();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RP_CORE_ASSERT(status, "Failed to intialize Glad!")

		RP_CORE_INFO("OpenGL Info: ");
		RP_CORE_INFO("    Vendor: {0}",   glGetString(GL_VENDOR));
		RP_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		RP_CORE_INFO("    Version: {0}",  glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		RP_PROFILE_FUNC();

		glfwSwapBuffers(m_WindowHandle);
	}

}	//	END namespace RAPIER

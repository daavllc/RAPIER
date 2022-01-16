#pragma once
#include "RAPIER/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace RAPIER
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

}	//	END namespace RAPIER

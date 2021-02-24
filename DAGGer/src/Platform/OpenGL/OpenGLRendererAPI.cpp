//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the OpenGL implementation for the RendererAPI.cpp file
#include "drpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/OpenGL/include/glad/glad.h>

namespace DAGGer
{
	void GLAPIENTRY OpenGLMessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		std::string msg = "[OpenGL] ";
		msg += message;
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         Dr_CORE_CRITICAL(msg); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       Dr_CORE_ERROR(msg); return;
			case GL_DEBUG_SEVERITY_LOW:          Dr_CORE_WARN(msg); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: Dr_CORE_TRACE(msg); return;
		}

		Dr_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		#ifdef Dr_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffers()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}	//	END namespace DAGGer

#pragma once

#include "RAPIER/Renderer/RenderCommand.h"

#include "RAPIER/Renderer/OrthographicCamera.h"
#include "RAPIER/Renderer/Shader.h"

namespace RAPIER
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();


		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};	//	END class Renderer

}	//	END namespace RAPIER



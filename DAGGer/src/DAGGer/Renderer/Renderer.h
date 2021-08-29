/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the definition for the user-end 3D renderer
////////////////////////////////
#pragma once

#include "DAGGer/Renderer/RenderCommand.h"

#include "DAGGer/Renderer/OrthographicCamera.h"
#include "DAGGer/Renderer/Shader.h"

namespace DAGGer
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

}	//	END namespace DAGGer



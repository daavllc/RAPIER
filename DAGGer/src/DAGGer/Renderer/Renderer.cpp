/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the implementation for the user-end Renderer
////////////////////////////////
#include "drpch.h"
#include "DAGGer/Renderer/Renderer.h"
#include "DAGGer/Renderer/Renderer2D.h"
#include "DAGGer/Renderer/SceneRenderer.h"

namespace DAGGer
{
	static RendererAPI* s_RendererAPI = nullptr;

	void Renderer::Init()
	{
		Dr_PROFILE_FUNCTION();

		RenderCommand::Init();
		SceneRenderer::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", SceneRenderer::s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}	//	END namespace DAGGer

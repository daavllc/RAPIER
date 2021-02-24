#include "drpch.h"
#include "SceneRenderer.h"

namespace DAGGer
{
	Scope<SceneRenderer::SceneRendererData> SceneRenderer::s_SceneData = CreateScope<SceneRenderer::SceneRendererData>();

	void SceneRenderer::Init()
	{

	}

	void SceneRenderer::SetViewportSize(uint32_t width, uint32_t height)
	{
		Dr_CORE_ASSERT(false, "Not implemented!");
	}

	void SceneRenderer::BeginScene(const Scene* scene, OrthographicCamera& camera)
	{
		Dr_CORE_ASSERT(!s_SceneData->ActiveScene, "");

		s_SceneData->ActiveScene = scene;

		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void SceneRenderer::EndScene()
	{
		s_SceneData->ActiveScene = nullptr;
	}

	void SceneRenderer::SubmitEntity(Entity* entity)
	{
		Dr_CORE_ASSERT(false, "Not implemented");
	}
}	//	END namespace DAGGer

#pragma once

#include "DAGGer/Scene/Entity.h"
#include "DAGGer/Renderer/OrthographicCamera.h"
#include <glm/glm.hpp>

namespace DAGGer
{
	class SceneRenderer
	{
	public:
		static void Init();

		static void SetViewportSize(uint32_t width, uint32_t height);

		static void BeginScene(const Scene* scene, OrthographicCamera& camera);
		static void EndScene();

		static void SubmitEntity(Entity* entity);

	private:
		struct SceneRendererData
		{
			const Scene* ActiveScene = nullptr;
			struct SceneInfo
			{
				Camera SceneCamera;
			};
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneRendererData> s_SceneData;

		friend class Renderer;
	};
}	//	END namespace DAGGer

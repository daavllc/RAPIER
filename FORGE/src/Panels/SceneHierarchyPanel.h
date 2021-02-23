#pragma once

#include "DAGGer/Scene/Scene.h"
#include "DAGGer/Core/Base.h"
#include "DAGGer/Scene/Entity.h"

namespace DAGGer
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);

		//template<typename T, typename... Args>
		//void DrawComponent<T>(Args&&... args);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}	//	END namespace DAGGer

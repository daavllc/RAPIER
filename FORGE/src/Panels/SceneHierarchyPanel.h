#pragma once

#include "RAPIER/Scene/Scene.h"
#include "RAPIER/Scene/Entity.h"
#include "RAPIER/Core/Base.h"

typedef int ImGuiTreeNodeFlags;

namespace RAPIER
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);

		void OnImGuiRender();
	private:
		void DrawComponentsView(Entity entity);
		void DrawEntityNode(Entity entity, const std::string& searchFilter = {});
		void DrawComponents(Entity entity, ImGuiTreeNodeFlags treeNodeFlags);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}	//	END namespace RAPIER

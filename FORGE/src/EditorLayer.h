#pragma once

#include <DAGGer.h>
#include "FORGE/src/Panels/SceneHierarchyPanel.h"

#include "DAGGer/Renderer/EditorCamera.h"

namespace DAGGer
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveScene();
		void SaveSceneAs();
	private:
		OrthographicCameraController m_CameraController;

		// TEMPORARY
		Ref<VertexArray> m_SquareVA;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;
		bool m_EnableVSync = true;

		EditorCamera m_EditorCamera;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = DrPos2(0.0f, 0.0f);
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;

		std::string m_FilePath;	//	Remeber filepath for Ctrl+S (Save)
	};

}	//	END namespace DAGGer
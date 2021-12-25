#pragma once

#include "DAGGer.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#include "DAGGer/Renderer/EditorCamera.h"

#include <filesystem>

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
		void UpdateWindowTitle();

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void OnOverlayRender();

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();

		//	UI Panels
		void UI_Toolbar();
		void Titlebar();
	private:
		float m_Time = 0.0f;
		int m_FrameCount = 0;
		float m_AverageFrameTime = 0.0f;
		OrthographicCameraController m_CameraController;

		// TEMPORARY
		Ref<VertexArray> m_SquareVA;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_EditorScene, m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		Entity m_HoveredEntity;

		bool m_PrimaryCamera = true;
		bool m_EnableVSync = false;

		EditorCamera m_EditorCamera;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_PlayButtonTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = DrPos2(0.0f, 0.0f);
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;

		bool m_ShowPhysicsColliders = false;

		enum class SceneState
		{
			Stop = 0, Play = 1,
			Edit = 2, Simulate = 3
		};
		SceneState m_SceneState = SceneState::Edit;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;


		std::filesystem::path m_EditorScenePath;	//	Remeber filepath for Ctrl+S (Save)

		//	Editor Resources
		Ref<Texture2D> m_IconPlay, m_IconPause, m_IconStop;
		Ref<Texture2D> m_IconMinimize, m_IconMaximize, m_IconClose;
	};

}	//	END namespace DAGGer

#pragma once

#include "EditorPanel.h"

#include "EditorConsole/ConsoleMessage.h"

#include "RAPIER/Renderer/Texture.h"

namespace RAPIER
{
	class EditorConsolePanel : public EditorPanel
	{
	public:
		EditorConsolePanel() {} // TODO
		~EditorConsolePanel() {} // TODO

		virtual void OnImGuiRender(bool& isOpen) override {} // TODO
		void OnScenePlay() {} // TODO

	private:
		void RenderMenu() {} // TODO
		void RenderConsole() {} // TODO
	private:
		static void PushMessage(const ConsoleMessage& message) {} // TODO
	private:
		Ref<Texture2D> m_InfoButton, m_WarningButton, m_ErrorButton;

		bool m_ShouldClearOnPlay = false;
		bool m_CollapseMessages = false;
		bool m_NewMessageAdded = false;

		static constexpr uint32_t s_MessageBufferCapacity = 500;

		std::array<ConsoleMessage, s_MessageBufferCapacity> s_MessageBuffer;
		uint32_t m_MessageBufferBegin = 0;
		int32_t m_MessageFilters = (int16_t)ConsoleMessage::Category::Info | (int16_t)ConsoleMessage::Category::Warning | (int16_t)ConsoleMessage::Category::Error;

		ConsoleMessage* m_SelectedMessage = nullptr;
		bool m_DisplayMessageInspector = false;
		bool m_IsMessageInspectorHovered = false;
	private:
		friend class EditorConsoleSink;
	};
}	// END namespace RAPIER

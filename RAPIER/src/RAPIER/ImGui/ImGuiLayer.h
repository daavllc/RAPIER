#pragma once

#include "RAPIER/Core/Layer.h"

#include "RAPIER/Core/Events/KeyEvent.h"
#include "RAPIER/Core/Events/MouseEvent.h"
#include "RAPIER/Core/Events/ApplicationEvent.h"

// ImGui uses OpenGL only

namespace RAPIER
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_FontSize = 16.0f;

	};	//	END class ImGuiLayer

}	//	END namespace RAPIER

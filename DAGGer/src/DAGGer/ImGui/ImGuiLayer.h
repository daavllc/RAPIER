//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the definition for ImGui layers
////////////////////////////////
#pragma once

#include "DAGGer/Core/Layer.h"

#include "DAGGer/Events/KeyEvent.h"
#include "DAGGer/Events/MouseEvent.h"
#include "DAGGer/Events/ApplicationEvent.h"

// ImGui uses OpenGL only

namespace DAGGer
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
		float m_FontSize = 18.0f;

	};	//	END class ImGuiLayer

}	//	END namespace DAGGer

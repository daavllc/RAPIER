/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted definitions for creating an application
/////////////////////////////
#pragma once

#include "DAGGer/Core/Base.h"

#include "DAGGer/Core/Window.h"
#include "DAGGer/Core/LayerStack.h"
#include "DAGGer/Events/Event.h"
#include "DAGGer/Events/ApplicationEvent.h"

#include "DAGGer/Core/Timestep.h"

#include "DAGGer/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace DAGGer
{
	class Application
	{
	public:
		Application(const std::string& name = "DAGGer Application");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}	//	END namespace DAGGer


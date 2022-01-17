#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Timestep.h"
#include "RAPIER/Core/Timer.h"
#include "RAPIER/Core/Window.h"
#include "RAPIER/Core/LayerStack.h"

#include "RAPIER/Core/Events/Event.h"
#include "RAPIER/Core/Events/ApplicationEvent.h"


#include "RAPIER/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace RAPIER
{
	struct ApplicationSpecification
	{
		std::string Name = "RAPIER Application";
		uint32_t WindowWidth = 1600, WindowHeight = 900;
		bool Decorations = true;
		bool Fullscreen = false;
		bool VSync = true;
		bool StartMaximized = true;
		bool Resizeable = true;
		bool EnableImGui = true;
		std::string WorkingDirectory;
	};
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			RP_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};
	class Application
	{
	public:
		Application(const ApplicationSpecification& specification, ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();
		void Close();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate(Timestep ts) {}

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);
		void RenderImGui();

		std::string OpenFile(const char* filter = "All\0*.*\0") const;
		std::string OpenFolder(const char* initialFolder = "") const;
		std::string SaveFile(const char* filter = "All\0*.*\0") const;

		inline void SetShowStats(bool show) { m_ShowStats = show; }

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }

		static const char* GetConfigurationName();
		static const char* GetPlatformName();

		inline const ApplicationSpecification& GetSpecification() const { return m_Specification; }

		inline ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

		inline PerformanceProfiler* GetPerformanceProfiler() { return m_Profiler; }

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ApplicationSpecification m_Specification;
		ApplicationCommandLineArgs m_CommandLineArgs;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		Timestep m_Timestep = 0.0f;
		float m_LastFrameTime = 0.0f;
		PerformanceProfiler* m_Profiler = nullptr;
		bool m_ShowStats = true;

		bool m_EnableVSync = true;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);

}	//	END namespace RAPIER


/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as abstracted implementation for creating an application
/////////////////////////////
#include "drpch.h"
#include "DAGGer/Core/Application.h"

#include "DAGGer/Core/Log.h"

#include "DAGGer/Renderer/Renderer.h"
#include "DAGGer/Renderer/RendererAPI.h"

#include "DAGGer/Core/Input.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

#include <filesystem>

extern ImGuiContext* GImGui;

namespace DAGGer
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification, ApplicationCommandLineArgs args)
		: m_Specification(specification), m_CommandLineArgs(args)
	{
		Dr_PROFILE_FUNCTION();
		Dr_CORE_ASSERT(!s_Instance, "Application already exists!");

		s_Instance = this;

		if (!specification.WorkingDirectory.empty())
			std::filesystem::current_path(specification.WorkingDirectory);

		m_Profiler = new PerformanceProfiler();

		WindowSpecification windowSpec;
		windowSpec.Title      = specification.Name;
		windowSpec.Width      = specification.WindowWidth;
		windowSpec.Height     = specification.WindowHeight;
		windowSpec.Fullscreen = specification.Fullscreen;
		windowSpec.VSync      = specification.VSync;
		m_Window = Window::Create(windowSpec);
		m_Window->SetEventCallback(Dr_BIND_EVENT_FN(Application::OnEvent));
		if (specification.StartMaximized)
			m_Window->Maximize();
		else
			m_Window->CenterWindow();
		m_Window->SetResizable(specification.Resizeable);

		Renderer::Init();
		if (m_Specification.EnableImGui)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}
	}

	Application::~Application()
	{
		Dr_PROFILE_FUNCTION();

		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}

		Renderer::Shutdown();

		delete m_Profiler;
		m_Profiler = nullptr;
	}

	void Application::PushLayer(Layer* layer)
	{
		Dr_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		Dr_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_LayerStack.PopOverlay(layer);
		layer->OnDetach();
	}

	void Application::RenderImGui()
	{
		Dr_SCOPE_PERF("Application::RenderImGui");

		m_ImGuiLayer->Begin();

		if (m_ShowStats)
		{

			ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));

			ImGui::Begin("Renderer");
			//auto& caps = RendererAPI::GetCapabilities();
			//ImGui::Text("Vendor: %s",   caps.Vendor.c_str());
			//ImGui::Text("Renderer: %s", caps.Device.c_str());
			//ImGui::Text("Version: %s",  caps.Version.c_str());
			ImGui::Separator();
			ImGui::Text("Frame Time: %.2fms\n", m_Timestep.GetMilliseconds());

			if (ImGui::Checkbox("VSync", &m_EnableVSync))
				m_Window->SetVSync(m_EnableVSync);
			ImGui::End();


			ImGui::Begin("Performance");
			ImGui::Text("Frame Time: %.2fms\n", m_Timestep.GetMilliseconds());
			const auto& perFrameData = m_Profiler->GetPerFrameData();
			for (auto&& [name, time] : perFrameData)
			{
				ImGui::Text("%s: %.3fms\n", name, time);
			}
			ImGui::End();

		}

		m_Profiler->Clear();

		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
	}


	void Application::Run()
	{
		Dr_PROFILE_FUNCTION();

		while (m_Running)
		{
			Dr_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			m_Timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					Dr_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(m_Timestep);
				}
				if (m_Specification.EnableImGui)
				{
					Dr_PROFILE_SCOPE("LayerStack OnImGuiRender");
					this->RenderImGui();
					m_ImGuiLayer->End();
				}
			}

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		Dr_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(Dr_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(Dr_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		Dr_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	const char* Application::GetConfigurationName()
	{
		#if defined(Dr_DEBUG)
			return "Debug";
		#elif defined(Dr_RELEASE)
			return "Release";
		#elif defined(Dr_DISTRIBUTION)
			return "Distribution";
		#else
			#error Undefined configuration?
		#endif
	}

	const char* Application::GetPlatformName()
	{
		#if defined(Dr_PLATFORM_WINDOWS)
			return "Windows x86_64";
		#else
			#error Undefined platform?
		#endif
	}


}	//	END namespace DAGGer

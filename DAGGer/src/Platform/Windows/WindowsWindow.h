//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the Windows definitions for the Window.h file
#pragma once

#include "DAGGer/Core/Window.h"
#include "DAGGer/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

namespace DAGGer
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& specification);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		virtual std::pair<uint32_t, uint32_t> GetSize() const override { return { m_Data.Width, m_Data.Height }; }
		virtual std::pair<float, float> GetWindowPos() const override;

		//	Window Attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSyncEnabled() const override;
		virtual void SetResizable(bool resizable) const override;
		virtual void SetDecorations(bool enabled) const override;

		virtual void Maximize() override;
		virtual void CenterWindow() override;

		virtual const std::string& GetTitle() const override { return m_Data.Title; }
		virtual void SetTitle(const std::string& title) override;

		inline virtual void* GetNativeWindow() const { return m_Window; };
	private:
		virtual void Init(const WindowSpecification& specification);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GLFWcursor* m_ImGuiMouseCursors[9] = { 0 };
		WindowSpecification m_Specification;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			bool Decorations;

			EventCallbackFn EventCallback;
		};	//	END struct WindowData

		WindowData m_Data;
		float m_LastFrameTime = 0.0f;

		Scope<GraphicsContext> m_Context;
	};	//	END class WindowsWindow

}	//	END namespace DAGGer


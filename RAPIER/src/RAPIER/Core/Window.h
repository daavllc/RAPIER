#pragma once

#include "rppch.h"

#include "RAPIER/Core/Base.h"
#include "RAPIER/Events/Event.h"

#include <functional>

namespace RAPIER
{
	struct WindowSpecification
	{
		std::string Title = "RAPIER Application";
		uint32_t Width = 1600, Height = 900;
		bool Fullscreen = false;
		bool VSync = true;
		bool Decorations = true;
	};

	// Interface representing a desktop system based window
	class Window : public RefCounted
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		inline virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
		virtual std::pair<float, float> GetWindowPos() const = 0;

		virtual void Maximize() = 0;
		virtual void CenterWindow() = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;
		virtual void SetResizable(bool resizable) const = 0;
		virtual void SetDecorations(bool enabled) const = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual void SetTitle(const std::string& title) = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowSpecification& specification = WindowSpecification());

	};	//	END class Window

}	//	END namespace RAPIER

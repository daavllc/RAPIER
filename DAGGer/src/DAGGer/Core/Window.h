/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as abstracted definitions for creating a Window
////////////////////////////////
#pragma once

#include "drpch.h"

#include "DAGGer/Core/Base.h"
#include "DAGGer/Events/Event.h"

namespace DAGGer
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "DAGGer Application",
				uint32_t width = 1600,
				uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};	//	END struct WindowProps

	// Interface representing a desktop system based window
	class Window : public RefCounted
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());

	};	//	END class Window

}	//	END namespace DAGGer

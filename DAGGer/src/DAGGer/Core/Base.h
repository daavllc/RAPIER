/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the base for DAGGer (crazy right?)
//    Also includes CoreConfig.h for DAGGer defines
///////////////////////
/*
    DAGGer Includes: (Thank you!)
      -  spdlog..........(logging)
      -  GLFW............(cross-platform windowing system)
      -  glad............(modern loader for OpenGL / Vulkan)
      -  glm.............(complex mathematics)
      -  ImGui...........(debug GUI)
      -  ImGuizmo........(3D gizmos)
      -  stb_image.......(load images)
      -  EnTT............(Entity Component System)
      -  yaml-cpp........(Saving/loading scenes for FORGE)

----------------------    Structure of DAGGer    -------------------------
Note: This isn't important information unless you're trying to understand the engine, or make changes to DAGGer itself.

Let's start off in chronological order:
    Entry.h (contains the int main() function)
      - Entry Initalizes logs then controls 3 main tasks
      - Startup, Runtime, Shutdown

  ------  Startup  --------------------------------------------------------------------
       Application.h CreateApplication (implemented in SandboxApp.cpp) 
         - This returns a new Sandbox and preforms a bunch of functions
           Application::Application (The application constructor)
             - Only 1 application may be created, then Window.h Create() is called
                WindowsWindow::Init() 
                  - initalizes glfw, and creates a glfwWindow then calls GraphicsContext::Create()
                    GraphicsContext::Create() 
                      - Uses the defined GraphicsAPI and calls API::Init
                        OpenGL - OpenGLContext::Init(GLFWwindow* windowHandle)
                          - Makes window context current then loads Glad
           Application::Application then calls Renderer::Init()
               Renderer::Init - Calls RenderCommand::Init() then Renderer2D::Init()
                 RenderCommand::Init() calls API::RendererAPI::Init()
                     OpenGL - OpenGLRendererAPI::Init() Initalizes OpenGL with default values
                 Renderer2D::Init() Creates API specific VertexArrays, and VertexBuffers
                     OpenGL - OpenGLVertexArray::AddVertexBuffer() adds a default vertex buffer to OpenGL
                     OpenGL - OpenGLIndexBuffer::AddIndexBuffer() adds a default index buffer to OpenGL (or an empty one)
                     OpenGL - OpenGLTexture2D is constructed and has SetData is called
                     OpenGL - OpenGLShader is constructed
                            The shader file is read, processes, and compiled
                     OpenGL - OpenGLShader::SetIntArray is called to conclude Renderer2D::Init and Renderer::Init
             Application::PushOverlay is called, and the ImGui layer is attached
       The Orthographic Camera is the created

  ------  Runtime  ------------------------------------
      Application::Run is called from entry.h
        LayerStack::OnUpdate is called
          Sandbox::OnUpdate is called
            OrthographicCameraController::OnUpdate is called
              OrthographicCamera::RecalculateViewMatrix is called
            Then Sandbox::OnUpdate is called

  ------  Shutdown  -----------------------------------
      OpenGLTexture2D is deconstructed
      WindowsWindow::Shutdown is called
      WindowsWindow is deconstructed
*/
#pragma once

#include <memory>
#include "Ref.h"

#include "DAGGer/Core/PlatformDetection.h"

#include "CoreConfig.h" //  includes DAGGer defines
#include "Log.h"
#include "Assert.h"

namespace DAGGer
{
	void InitalizeCore();
	void ShutdownCore();
}	//	END namespace DAGGer

#ifndef Dr_PLATFORM_WINDOWS
	#error DAGGer only supports Windows!
#endif

#define Dr_RENDERER_OPENGL

#ifdef Dr_DEBUG
    #if defined(Dr_PLATFORM_WINDOWS)
        #define Dr_DEBUGBREAK() __debugbreak()
    #elif defined(Dr_PLATFORM_LINUX)
        #include <signal.h>
        #define Dr_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define Dr_ENABLE_ASSERTS
#else
    #define Dr_DEBUGBREAK()
#endif

#define Dr_EXPAND_MACRO(x) x
#define Dr_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define Dr_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace DAGGer
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}	//	END namespace DAGGer

#include "DAGGer/Core/Log.h"
#include "DAGGer/Core/Assert.h"

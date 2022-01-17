//------------------------------------------------------------------------------
//----======================================================================----
//----=                   ____  ___    ____  ______________                =----
//----=                  / __ \/   |  / __ \/  _/ ____/ __ \               =----
//----=                 / /_/ / /| | / /_/ // // __/ / /_/ /               =----
//----=                / _, _/ ___ |/ ____// // /___/ _, _/                =----
//----=               /_/ |_/_/  |_/_/   /___/_____/_/ |_|                 =----
//----======================================================================----
// Author: DAAV, LLC (https://github.com/daavofficial)
//	License : MIT
//	Language: C++17
//	Include this file in your RAPIER application
///////////////////////////////////////////////////
#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Assert.h"				//	Defines to RAPIER Asserts
#include "RAPIER/Core/Log.h"				//	Class for accessing logging functions

#include "RAPIER/Core/Application.h"		//	Abstracted class for applications
#include "RAPIER/Core/Layer.h"				//	Class for managing layers
#include "RAPIER/Core/Timestep.h"			//	Allows updates based on real time instead of frame time
#include "RAPIER/Core/Timer.h"				//	Definition for timer

//  --------------  Event headers  --------------  //
#include "RAPIER/Core/Events/Event.h"
#include "RAPIER/Core/Events/ApplicationEvent.h"
#include "RAPIER/Core/Events/KeyEvent.h"
#include "RAPIER/Core/Events/MouseEvent.h"

//  --------------  Input headers  --------------  //
#include "RAPIER/Core/Input.h"				//	Main input header file 
#include "RAPIER/Core/KeyCodes.h"			//	RAPIER Key Codes
#include "RAPIER/Core/MouseCodes.h"			//	RAPIER Mouse button codes
// ----------------------------------------------  //

#include "RAPIER/Renderer/OrthographicCameraController.h"	//	Class for controlling the orthographic camera

#include "RAPIER/ImGui/ImGuiLayer.h"		//	Debug class for implementing ImGui
//  --------------  Scene headers  --------------  //
#include "RAPIER/Scene/Scene.h"				//	Scene class for the ECS
#include "RAPIER/Scene/Entity.h"			//	Entity class for the ECS
#include "RAPIER/Scene/ScriptableEntity.h"	//	Native scriptable entity class
#include "RAPIER/Scene/Components.h"		//	Struct for components
// ----------------------------------------------  //

//  --------------  Renderer headers  --------------  //
#include "RAPIER/Renderer/Renderer.h"		//	User-end 3D Render commands
#include "RAPIER/Renderer/Renderer2D.h"		//	User-end 2D Render commands
#include "RAPIER/Renderer/RenderCommand.h"	//	Backend RAPIER Render commands
#include "RAPIER/Renderer/RendererCapabilities.h"	//	Renderer Capabilities

#include "RAPIER/Renderer/Buffer.h"			//	Abstracted class for Vertex and Index buffers
#include "RAPIER/Renderer/Shader.h"			//	Abstracted class for shaders
#include "RAPIER/Renderer/Framebuffer.h"	//	Abstracted class for Framebuffers
#include "RAPIER/Renderer/Texture.h"		//	Abstracted class for textures
#include "RAPIER/Renderer/VertexArray.h"	//	Abstracted class for Vertex Arrays
#include "RAPIER/Renderer/SubTexture2D.h"	//	Abstracted class for 2D SubTextures

#include "RAPIER/Renderer/OrthographicCamera.h"	//	Class for implementing a camera
//  ------------------------------------------------  //

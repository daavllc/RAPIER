//------------------------------------------------------------------------------------------------------------
//----====================================================================================================~~~~
//----=                                                                                                  =----
//----=               MMMM        MMMM        MMMM        MMMM                                           =----
//----=               M   M      M    M      M           M                                               =----
//----=               M   M      M    M      M           M           MMMM      MMM                       =----
//----=               M   M      MMMMMM      M  MMM      M  MMM      M         M  M                      =----
//----=               M   M      M    M      M    M      M    M      MMM       MMM                       =----
//----=               M   M      M    M      M    M      M    M      M         M  M                      =----
//----=               MMMM       M    M       MMMM        MMMM       MMMM      M  M                      =---- 
//----=                                                                                                  =----
//----====================================================================================================~~~~
//----=----------------------------------------  version 0.2.1a  ----------------------------------------=----
//----====================================================================================================----
// Author: Anonoei (https://github.com/anonoei)
//	License : GPLv3
//	Language: C++17
//	Dependencies: A Sandbox Application
//	This is the include file for DAGGer... the DA Gordian Graphics Engine Reimagined (I'm not full of myself)
//		If you're interested, there's more information about the engine inside DAGGer/Core/Base.h - Thanks for checking it out! :)
//	For some useful libraries, be sure to check out DAALS - There's a lot of functionality there!
///////////////////////////////////////////////////
#pragma once

// This file is included inside DAGGer Applications

#include "DAGGer/Core/Base.h"

#include "DAGGer/Core/Application.h"		//	Abstracted class for applications
#include "DAGGer/Core/Layer.h"				//	Class for managing layers
#include "DAGGer/Core/Log.h"				//	Class for accessing logging functions

#include "DAGGer/Core/Timestep.h"			//	Allows updates based of real time instead of frame time
//  --------------  Input headers  --------------  //
#include "DAGGer/Core/Input.h"				//	Main input header file 
#include "DAGGer/Core/KeyCodes.h"			//	DAGGer Key Codes
#include "DAGGer/Core/MouseCodes.h"			//	DAGGer Mouse button codes
// ----------------------------------------------  //

#include "DAGGer/Renderer/OrthographicCameraController.h"	//	Class for controlling the orthographic camera

#include "DAGGer/ImGui/ImGuiLayer.h"		//	Debug class for implementing ImGui
//  --------------  Scene headers  --------------  //
#include "DAGGer/Scene/Scene.h"				//	Scene class for the ECS
#include "DAGGer/Scene/Entity.h"			//	Entity class for the ECS
#include "DAGGer/Scene/Components.h"		//	Struct for components
// ----------------------------------------------  //

//  --------------  Renderer headers  --------------  //
#include "DAGGer/Renderer/Renderer.h"		//	User-end 3D Render commands
#include "DAGGer/Renderer/Renderer2D.h"		//	User-end 2D Render commands
#include "DAGGer/Renderer/RenderCommand.h"	//	Backend DAGGer Render commands

#include "DAGGer/Renderer/Buffer.h"			//	Abstracted class for Vertex and Index buffers
#include "DAGGer/Renderer/Shader.h"			//	Abstracted class for shaders
#include "DAGGer/Renderer/Framebuffer.h"	//	Abstracted class for Framebuffers
#include "DAGGer/Renderer/Texture.h"		//	Abstracted class for textures
#include "DAGGer/Renderer/SubTexture2D.h"	//	Abstracted class for 2D SubTextures
#include "DAGGer/Renderer/VertexArray.h"	//	Abstracted class for Vertex Arrays

#include "DAGGer/Renderer/OrthographicCamera.h"	//	Class for implementing a camera
//  ------------------------------------------------  //

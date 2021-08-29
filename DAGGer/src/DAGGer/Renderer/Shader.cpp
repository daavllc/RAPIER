/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted implementation of Shaders
//////////////////////////////
#include "drpch.h"
#include "DAGGer/Renderer/Shader.h"

#include "DAGGer/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace DAGGer
{

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLShader>::Create(filepath);
			case RendererAPI::API::Vulkan:		Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		Dr_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLShader>::Create(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::Vulkan:		Dr_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		Dr_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		Dr_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	const Ref<Shader> ShaderLibrary::Get(const std::string& name) const
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		Dr_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders.at(name);
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		Dr_PROFILE_RENDERER_FUNCTION();

		return m_Shaders.find(name) != m_Shaders.end();
	}
	
}	//	END namespace DAGGer

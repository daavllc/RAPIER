#include "rppch.h"
#include "RAPIER/Renderer/Shader.h"

#include "RAPIER/Renderer/Renderer.h"
#include "RAPIER/Platform/OpenGL/OpenGLShader.h"

namespace RAPIER
{

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLShader>::Create(filepath);
			case RendererAPI::API::Vulkan:		RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		RP_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");  return nullptr;
			case RendererAPI::API::OpenGL:		return Ref<OpenGLShader>::Create(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::Vulkan:		RP_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported!"); return nullptr;
		}

		RP_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		RP_PROFILE_RENDERER_FUNCTION();

		RP_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		RP_PROFILE_RENDERER_FUNCTION();

		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		RP_PROFILE_RENDERER_FUNCTION();

		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		RP_PROFILE_RENDERER_FUNCTION();

		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	const Ref<Shader> ShaderLibrary::Get(const std::string& name) const
	{
		RP_PROFILE_RENDERER_FUNCTION();

		RP_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders.at(name);
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		RP_PROFILE_RENDERER_FUNCTION();

		return m_Shaders.find(name) != m_Shaders.end();
	}
	
}	//	END namespace RAPIER

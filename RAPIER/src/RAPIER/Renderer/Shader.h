#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace RAPIER
{
	class Shader : public RefCounted
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const void SetInt(const std::string& name, int value) const = 0;
		virtual const void SetIntArray(const std::string& name, int* values, uint32_t count) const = 0;
		virtual const void SetFloat(const std::string& name, float) const = 0;
		virtual const void SetFloat2(const std::string& name, const glm::vec2& value) const = 0;
		virtual const void SetFloat3(const std::string& name, const glm::vec3& value) const = 0;
		virtual const void SetFloat4(const std::string& name, const glm::vec4& value) const = 0;
		virtual const void SetMat4(const std::string& name, const glm::mat4& value) const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary : public RefCounted
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		const Ref<Shader> Get(const std::string& name) const;

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}	//	END namespace RAPIER

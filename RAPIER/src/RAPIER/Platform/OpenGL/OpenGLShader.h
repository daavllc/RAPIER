#pragma once

#include "RAPIER/Renderer/Shader.h"

#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace RAPIER
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const void SetInt(const std::string& name, int value) const override;
		virtual const void SetIntArray(const std::string& name, int* values, uint32_t count) const override;
		virtual const void SetFloat(const std::string& name, float value) const override;
		virtual const void SetFloat2(const std::string& name, const glm::vec2& value) const override;
		virtual const void SetFloat3(const std::string& name, const glm::vec3& value) const override;
		virtual const void SetFloat4(const std::string& name, const glm::vec4& value) const override;
		virtual const void SetMat4(const std::string& name, const glm::mat4& value) const override;

		virtual const std::string& GetName() const override { return m_Name; }

		const void UploadUniformInt(const std::string& name, int value) const;
		const void UploadUniformIntArray(const std::string& name, int* values, uint32_t count) const;

		const void UploadUniformFloat(const std::string& name, float value) const;
		const void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
		const void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
		const void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const;

		const void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		const void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		
		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;

		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};

}	//	END namespace RAPIER

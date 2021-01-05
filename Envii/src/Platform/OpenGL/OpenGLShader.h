#pragma once

#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Render/Shader.h"

namespace Envii
{
	static std::unordered_map<ShaderType, GLenum> shaderTypeMap = {
		{ ShaderType::VERTEX, GL_VERTEX_SHADER },
		{ ShaderType::FRAGMENT, GL_FRAGMENT_SHADER },
		{ ShaderType::GEOMETRY, GL_GEOMETRY_SHADER }
	}; 

	static std::unordered_map<GLenum, std::string> shaderTypeStringMap = {
		{ GL_VERTEX_SHADER,	"Vertex" },
		{ GL_FRAGMENT_SHADER, "Fragment" },
		{ GL_GEOMETRY_SHADER, "Geometry" }
	};
	
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetUniformMat3f(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4) override;
		virtual void SetUniform3f(const std::string& name, float f1, float f2, float f3) override;
		virtual void SetUniform2f(const std::string& name, float f1, float f2) override;
		virtual void SetUniform1f(const std::string& name, float f1) override;
		virtual void SetUniform1i(const std::string& name, unsigned int val) override;
		virtual void SetUniform1iv(const std::string& name, unsigned int size, int* vals) override;

	private:
		const int GetUniformLocation(const std::string& name);

		std::unordered_map<ShaderType, std::string> ParseShaders(const std::string& srcPath);
		GLuint CompileShader(GLenum shaderType, const std::string& src);
		GLuint CreateShaderProgram(const std::unordered_map<ShaderType, std::string> sourceMap);
		GLuint CreateShaderProgram(const std::string& vertSrc, const std::string& fragSrc);

	private:
		uint32_t m_Id;
		std::string m_Name;
		std::string m_FilePath;
		std::unordered_map<std::string, int> m_UniformLocCache;
	};

}
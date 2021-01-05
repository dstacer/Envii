#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Envii
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
		GEOMETRY = 2,
		NUM_TYPES
	}; 
	
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetUniformMat3f(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4) = 0;
		virtual void SetUniform3f(const std::string& name, float f1, float f2, float f3) = 0;
		virtual void SetUniform2f(const std::string& name, float f1, float f2) = 0;
		virtual void SetUniform1f(const std::string& name, float f1) = 0;
		virtual void SetUniform1i(const std::string& name, unsigned int val) = 0;
		virtual void SetUniform1iv(const std::string& name, unsigned int size, int* vals) = 0;
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};
}
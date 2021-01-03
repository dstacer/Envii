#include "evpch.h"

#include "Render/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Envii
{
	// Shader Impls
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetApi())
		{
			case RenderApi::Api::NONE:
			{
				EV_CORE_ASSERT(false, "Envii doesn't currently support headless config.");
				return nullptr;
			}
			case RenderApi::Api::OPENGL:
			{
				return std::make_shared<OpenGLShader>(filepath);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
	{
		switch (Renderer::GetApi())
		{
			case RenderApi::Api::NONE:
			{
				EV_CORE_ASSERT(false, "Envii doesn't currently support headless config.");
				return nullptr;
			}
			case RenderApi::Api::OPENGL:
			{
				return std::make_shared<OpenGLShader>(name, vertSrc, fragSrc);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
	
	// The functions below are temporary, until the shader classes are finished.  This class shouldn't
	// know about any graphics-api-specific implementing subclasses.
	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniformMat4f(name, matrix);
	}

	void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniformMat3f(name, matrix);
	}

	void Shader::SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniform4f(name, f1, f2, f3, f4);
	}

	void Shader::SetUniform3f(const std::string& name, float f1, float f2, float f3)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniform3f(name, f1, f2, f3);
	}

	void Shader::SetUniform2f(const std::string& name, float f1, float f2)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniform2f(name, f1, f2);
	}

	void Shader::SetUniform1f(const std::string& name, float f1)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniform1f(name, f1);
	}

	void Shader::SetUniform1i(const std::string& name, unsigned int val)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniform1i(name, val);
	}

	void Shader::SetUniform1iv(const std::string& name, unsigned int size, int* vals)
	{
		OpenGLShader* shader = (OpenGLShader*)this;
		return shader->SetUniform1iv(name, size, vals);
	}

	// ShaderLibrary impls
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		const auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		EV_CORE_ASSERT(!Exists(name), "Shader already exists in library.");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		EV_CORE_ASSERT(Exists(name),"No shader named {0} found in library.", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
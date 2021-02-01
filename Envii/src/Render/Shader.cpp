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
				return CreateRef<OpenGLShader>(filepath);
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
				return CreateRef<OpenGLShader>(name, vertSrc, fragSrc);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
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
#include "evpch.h"

#include "Render/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Render/Buffer.h"

namespace Envii
{
	Shader* Shader::Create(const std::string& filepath)
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
				return new OpenGLShader(filepath);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
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
			return new OpenGLShader(vertSrc, fragSrc);
		}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}
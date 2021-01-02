#include "evpch.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Renderer.h"

namespace Envii
{
	Texture2D* Texture2D::Create(uint32_t width, uint32_t height, void* data)
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
				return new OpenGLTexture2D(width, height, data);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr; 
	}

	Texture2D* Texture2D::Create(const std::string& filepath)
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
				return new OpenGLTexture2D(filepath);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}



#include "evpch.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Renderer.h"

namespace Envii
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t numChannels)
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
			return CreateRef<OpenGLTexture2D>(width, height, numChannels);
		}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t numChannels, void* data)
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
				return CreateRef<OpenGLTexture2D>(width, height, numChannels, data);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr; 
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath, uint32_t texSlot)
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
				return CreateRef<OpenGLTexture2D>(filepath, texSlot);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}



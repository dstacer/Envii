#include "evpch.h"
#include "Platform/OpenGL/OpenGLTexture2DArray.h"
#include "Renderer.h"

namespace Envii
{
	Texture2DArray* Texture2DArray::Create(const std::vector<std::string> filepaths)
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
				return new OpenGLTexture2DArray(filepaths);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}

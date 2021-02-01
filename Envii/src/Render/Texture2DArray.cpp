#include "evpch.h"
#include "Platform/OpenGL/OpenGLTexture2DArray.h"
#include "Renderer.h"

namespace Envii
{
	Ref<Texture2DArray> Texture2DArray::Create(const std::vector<std::string> filepaths, uint32_t texSlot)
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
				return CreateRef<OpenGLTexture2DArray>(filepaths, texSlot);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}

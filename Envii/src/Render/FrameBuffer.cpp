#include "evpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"


namespace Envii
{
	Ref<FrameBuffer> FrameBuffer::Create(const FbSpecs& specs)
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
				return CreateRef<OpenGLFrameBuffer>(specs);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}
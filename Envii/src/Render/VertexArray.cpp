#include "evpch.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Envii
{
	VertexArray* VertexArray::Create()
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
				return new OpenGLVertexArray();
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}
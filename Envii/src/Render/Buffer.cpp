#include "evpch.h"

#include "Render/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Render/Buffer.h"

namespace Envii
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
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
				return CreateRef<OpenGLVertexBuffer>(size);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
	
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
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
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
			}
		}

		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
				return CreateRef<OpenGLIndexBuffer>(indices, count);
			}
		}
		EV_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}
}
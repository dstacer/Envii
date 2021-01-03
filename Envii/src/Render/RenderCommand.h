#pragma once

#include <glm/glm.hpp>
#include "RenderAPI.h"

namespace Envii
{
	class RenderCommand
	{
	public:
		inline static void Init() { s_RenderApi->Init(); }
		inline static void Clear() { s_RenderApi->Clear(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RenderApi->SetClearColor(color); }
		
		inline static void SetBlendFunc(uint32_t srcFactor, uint32_t destFactor) 
		{
			s_RenderApi->SetBlendFunc(srcFactor, destFactor);
		}

		inline static void SetBlendEnable(bool enable) 
		{
			s_RenderApi->SetBlendEnable(enable);
		}

		inline static void SetViewport(uint32_t bottomX, uint32_t bottomY, uint32_t width, uint32_t height)
		{
			s_RenderApi->SetViewport(bottomX, bottomY, width, height);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RenderApi->DrawIndexed(vertexArray);
		}

	private:
		static RenderApi* s_RenderApi;
	};
}
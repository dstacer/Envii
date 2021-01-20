#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Envii
{
	class RenderApi
	{
	public:
		enum class Api
		{
			NONE = 0,
			OPENGL
		};

	public:
		virtual ~RenderApi() {}
		virtual void Init() const = 0;
		virtual void Clear() const = 0;
		virtual void SetClearColor(const glm::vec4& color) const = 0;
		virtual void SetBlendFunc(uint32_t srcFactor, uint32_t destFactor) const = 0;
		virtual void SetBlendEnable(bool enable) const = 0;
		virtual void SetDepthTestEnable(bool enable) const = 0;
		virtual void SetViewport(uint32_t bottomX, uint32_t bottomY, uint32_t width, uint32_t height) const = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) const = 0;

		inline static Api GetApi() { return s_Api; }

	private:
		static Api s_Api;
	};
}
#pragma once

#include "Render/RenderAPI.h"

namespace Envii
{
	class OpenGLRenderApi : public RenderApi
	{
		virtual void Init() const override; 
		virtual void Clear() const override;
		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) const override;
		virtual void SetBlendFunc(uint32_t srcFactor, uint32_t destFactor) const override;
		virtual void SetBlendEnable(bool enable) const override;
	};
}
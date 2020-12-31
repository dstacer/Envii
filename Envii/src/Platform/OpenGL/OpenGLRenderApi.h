#pragma once

#include "Render/RenderAPI.h"

namespace Envii
{
	class OpenGLRenderApi : public RenderApi
	{
		virtual void Clear() const override;
		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const override;
	};
}
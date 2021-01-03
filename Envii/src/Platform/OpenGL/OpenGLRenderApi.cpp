#include "evpch.h"
#include <glad/glad.h>
#include "Render/Renderer.h"
#include "OpenGLRenderApi.h"


namespace Envii
{
	void OpenGLRenderApi::Init() const
	{
		SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SetBlendEnable(true);
	}
	
	void OpenGLRenderApi::Clear() const
	{
		GlApiCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRenderApi::SetClearColor(const glm::vec4& color) const
	{
		GlApiCall(glClearColor(color.r, color.g, color.b, color.a));
	}

	void OpenGLRenderApi::SetBlendFunc(uint32_t srcFactor, uint32_t destFactor) const
	{
		GlApiCall(glBlendFunc(srcFactor, destFactor));
	}

	void OpenGLRenderApi::SetBlendEnable(bool enable) const
	{
		if (!enable)
		{
			GlApiCall(glDisable(GL_BLEND));
		}
		else
		{
			GlApiCall(glEnable(GL_BLEND));
		}
	}

	void OpenGLRenderApi::SetViewport(uint32_t bottomX, uint32_t bottomY, uint32_t width, uint32_t height) const
	{
		GlApiCall(glViewport(bottomX, bottomY, width, height));
	}

	void OpenGLRenderApi::DrawIndexed(const Ref<VertexArray>& vertexArray) const
	{
		GlApiCall(glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));

	}
}
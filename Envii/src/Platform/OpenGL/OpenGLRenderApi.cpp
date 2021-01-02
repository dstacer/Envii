#include "evpch.h"
#include <glad/glad.h>
#include "OpenGLRenderApi.h"


namespace Envii
{
	void OpenGLRenderApi::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderApi::SetClearColor(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderApi::DrawIndexed(const Ref<VertexArray>& vertexArray) const
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}
}
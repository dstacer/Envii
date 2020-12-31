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
		virtual void Clear() const = 0;
		virtual void SetClearColor(const glm::vec4& color) const = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) const = 0;

		inline static Api GetApi() { return s_Api; }

	private:
		static Api s_Api;
	};
}
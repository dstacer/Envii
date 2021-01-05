#pragma once

#include <glm/glm.hpp>
#include "OrthoCamera.h"

namespace Envii
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float texId = 0.0f);
		

	};

	
}
#pragma once

#include <glm/glm.hpp>
#include "OrthoCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"

namespace Envii
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const OrthoCamera& camera);
		static void Flush();
		static void EndScene();

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture>& texture, float texCoordScale = 1.0f, uint32_t texId = 0);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<SubTexture2D>& subtex, float texCoordScale = 1.0f, uint32_t texId = 0);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuadRotate(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture>& texture, float rotation, float texCoordScale = 1.0f, uint32_t texId = 0);
		static void DrawQuadRotate(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<SubTexture2D>& subtex, float rotation, float texCoordScale = 1.0f, uint32_t texId = 0);
		static void DrawQuadRotate(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation);
		
		struct RenderStats
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
		};

		static void ResetStats();
		static const RenderStats& GetStats();
	
	private:
		static void StartNewBatch();
	};
}
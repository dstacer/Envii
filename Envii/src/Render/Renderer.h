#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthoCamera.h"

namespace Envii
{
	#define GlApiCall(x) ClearGlErrors(); x; EV_CORE_ASSERT(LogGlErrors(__FILE__, #x, __LINE__),"")

	void ClearGlErrors();
	bool LogGlErrors(const char* file, const char* function, int line);

	const size_t MAX_QUADS(10000);
	const size_t MAX_VERTS(4 * MAX_QUADS);
	const size_t MAX_INDICES(6 * MAX_QUADS);
	const size_t MAX_TEXTURES(32);

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexId;
	}; 

	class Renderer
	{
	public:
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();
		static void Submit(const Ref<VertexArray>& vertexArray,
						   const Ref<Shader>& shader,
						   const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderApi::Api GetApi() { return RenderApi::GetApi(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjMat;
		};

		static SceneData* s_SceneData;
	};
}
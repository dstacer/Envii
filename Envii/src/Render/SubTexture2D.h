#pragma once

#include <glm/glm.hpp>
#include "../Core/Core.h"
#include "Texture.h"

namespace Envii
{ 
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2 sizeInTiles, const glm::vec2 lowerLeft, const glm::vec2 upperRight);

		const glm::vec2* GetTexCoords() const { return m_TexCoords; }
		const Ref<Texture2D>& GetTexture() const { return m_Texture; }
		const glm::vec2& GetSizeInTiles() const { return m_SizeInTiles; }

		static Ref<SubTexture2D> CreateFromIndices(const Ref<Texture2D>& texture, glm::vec2 xyIndices, float pixPerTile, const glm::vec2 sizeInTiles = { 1, 1 });
			
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
		glm::vec2 m_SizeInTiles;
	};
}
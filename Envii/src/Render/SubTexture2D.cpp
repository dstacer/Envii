#include "evpch.h"
#include "SubTexture2D.h"

namespace Envii
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2 sizeInTiles, const glm::vec2 lowerLeft, const glm::vec2 upperRight)
		: m_Texture(texture),
		  m_SizeInTiles(sizeInTiles)
	{
		m_TexCoords[0] = { lowerLeft.x, lowerLeft.y };
		m_TexCoords[1] = { upperRight.x, lowerLeft.y };
		m_TexCoords[2] = { upperRight.x, upperRight.y };
		m_TexCoords[3] = { lowerLeft.x, upperRight.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromIndices(const Ref<Texture2D>& texture, glm::vec2 xyIndices, float pixPerTile, const glm::vec2 sizeInTiles)
	{
		glm::vec2 texCoordBounds[] = {
			{ xyIndices.x * pixPerTile /  texture->GetWidth(), xyIndices.y * pixPerTile / texture->GetHeight() },
			{ (xyIndices.x + sizeInTiles.x) * pixPerTile / texture->GetWidth(), (xyIndices.y + sizeInTiles.y) * pixPerTile / texture->GetHeight() }
		};

		return CreateRef<SubTexture2D>(texture, sizeInTiles, texCoordBounds[0], texCoordBounds[1]);
	}
}
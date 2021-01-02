#pragma once

#include <string>
#include <vector>
#include "Render/Texture2DArray.h"

namespace Envii
{
	class OpenGLTexture2DArray : public Texture2DArray
	{
	public:
		OpenGLTexture2DArray(const std::vector<std::string> filepaths);
		~OpenGLTexture2DArray();

		virtual void Bind(unsigned int texSlot = 0) const override;
		virtual void Unbind() const override;

		virtual int GetWidth() const override { return m_Width; }
		virtual int GetHeight() const override { return m_Height; }

	private:
		unsigned int m_RendererId;
		std::vector<std::string> m_Filepaths;
		unsigned char* m_Buffers[16];
		int m_Width, m_Height, m_Channels;
		int m_Layers;
	};
}

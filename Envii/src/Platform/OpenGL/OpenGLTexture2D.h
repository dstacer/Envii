#pragma once

#include <string>
#include "Render/Texture2D.h"

namespace Envii
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, void* data);
		OpenGLTexture2D(const std::string& filepath);

		~OpenGLTexture2D();

		virtual void Bind(unsigned int texSlot = 0) const override;
		virtual void Unbind() const override;

		virtual int GetWidth() const override { return m_Width; }
		virtual int GetHeight() const override { return m_Height; }
		virtual void SetData(void* data, uint32_t size) override;

	private:
		unsigned int m_RendererId;
		std::string m_Filepath;
		unsigned char* m_Buffer;
		int m_Width, m_Height, m_Channels;
	};
}

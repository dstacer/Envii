#pragma once

#include <string>
#include <vector>
#include "Render/Texture.h"

namespace Envii
{
	class OpenGLTexture2DArray : public Texture2DArray
	{
	public:
		OpenGLTexture2DArray(const std::vector<std::string> filepaths, uint32_t texSlot = 0);
		~OpenGLTexture2DArray();

		virtual void Bind(uint32_t texSlot = 0) const override;
		virtual void Unbind() const override;
		virtual uint32_t GetId() const override;
		virtual int GetWidth() const override { return m_Width; }
		virtual int GetHeight() const override { return m_Height; }
		virtual void SetData(void* data, uint32_t size) override;
		virtual bool operator==(const Texture& compareTo) const override
		{
			return m_Id == compareTo.GetId();
		}

	private:
		uint32_t m_Id;
		std::vector<std::string> m_Filepaths;
		unsigned char* m_Buffers[16];
		int m_Width, m_Height, m_Channels;
		uint32_t m_Layers;
	};
}

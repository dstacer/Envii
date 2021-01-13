#include "evpch.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "Render/Renderer.h"
#include "OpenGLTexture2DArray.h"

namespace Envii
{
	OpenGLTexture2DArray::OpenGLTexture2DArray(const std::vector<std::string> filepaths, uint32_t texSlot)
		: m_Id(0),
		  m_Filepaths(filepaths),
		  m_Width(0),
		  m_Height(0),
		  m_Channels(0),
		  m_Layers((uint32_t)filepaths.size() + 1)
	{
		// data is flipped for .png.  Must set appropriate for other
		// texture formats
		stbi_set_flip_vertically_on_load(true);
		for (int i = 0; i < m_Filepaths.size(); ++i)
		{
			m_Buffers[i + 1] = stbi_load(m_Filepaths[i].c_str(), &m_Width, &m_Height, &m_Channels, 0);
			EV_CORE_ASSERT(m_Buffers[i+1], "Unable to load texture data for {0}", m_Filepaths[i]);
		}

		// Set the first texture buffer to white.
		size_t bufferSize = (size_t)(m_Width * m_Height * m_Channels);
		m_Buffers[0] = (unsigned char*)malloc(bufferSize);
		memset(m_Buffers[0], 255, bufferSize);


		GlApiCall(glGenTextures(1, &m_Id));

		Bind(texSlot);

		uint32_t internalFormat, dataFormat;
		switch (m_Channels)
		{
			case 3:
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			}
			case 4:
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			}
		}
		EV_CORE_ASSERT(internalFormat && dataFormat, "Pixel data format not supported.");

		// Allocate the storage.
		GlApiCall(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internalFormat, m_Width, m_Height, m_Layers,
			0, dataFormat, GL_UNSIGNED_BYTE, nullptr));

		GlApiCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));

		// The following link helps clarify the uploading of the texture data in this loop:
		// https://stackoverflow.com/questions/52339703/problems-using-gltexsubimage3d-correctly
		for (uint32_t i = 0; i < m_Layers; ++i)
		{
			GlApiCall(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, m_Width, m_Height,
				1, dataFormat, GL_UNSIGNED_BYTE, m_Buffers[i]));

			if (m_Buffers[i])
				stbi_image_free(m_Buffers[i]);
		}
		Unbind();

	}

	OpenGLTexture2DArray::~OpenGLTexture2DArray()
	{
		GlApiCall(glDeleteTextures(1, &m_Id));
	}

	void OpenGLTexture2DArray::Bind(uint32_t texSlot) const
	{
		GlApiCall(glActiveTexture(GL_TEXTURE0 + texSlot));
		GlApiCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_Id));
	}

	void OpenGLTexture2DArray::Unbind() const
	{
		GlApiCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
	}

	uint32_t OpenGLTexture2DArray::GetId() const
	{
		return m_Id;
	}

	void OpenGLTexture2DArray::SetData(void* data, uint32_t size)
	{

	}
}

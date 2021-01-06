#include "evpch.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "Render/Renderer.h"
#include "OpenGLTexture2D.h"

namespace Envii
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t numChannels)
		: m_Id(0),
		m_Filepath(""),
		m_Buffer(nullptr),
		m_Width(width),
		m_Height(height),
		m_Channels(numChannels)
	{
		GlApiCall(glGenTextures(1, &m_Id));
		Bind();

		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		uint32_t internalFormat = 0, dataFormat = 0;
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

		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr));
		Unbind();
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t numChannels, void* data)
		: m_Id(0),
		m_Filepath(""),
		m_Buffer(nullptr),
		m_Width(width),
		m_Height(height),
		m_Channels(numChannels)
	{
		GlApiCall(glGenTextures(1, &m_Id));
		Bind();

		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		
		uint32_t internalFormat = 0, dataFormat = 0;
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

		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data));
		Unbind();
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath, uint32_t texSlot)
		: m_Id(0),
		  m_Filepath(filepath),
		  m_Buffer(nullptr),
		  m_Width(0),
		  m_Height(0),
		  m_Channels(0)
	{
		// data is flipped for .png.  Must set appropriately for other
		// texture formats
		stbi_set_flip_vertically_on_load(true);
		m_Buffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channels, 0);
		EV_CORE_ASSERT(m_Buffer, "Unable to load texture data for {0}", filepath);

		GlApiCall(glGenTextures(1, &m_Id));
		Bind(texSlot);

		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		uint32_t internalFormat = 0, dataFormat = 0;
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

		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_Buffer));
		Unbind();

		if (m_Buffer)
			stbi_image_free(m_Buffer);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		GlApiCall(glDeleteTextures(1, &m_Id));
	}

	void OpenGLTexture2D::Bind(uint32_t texSlot) const
	{
		GlApiCall(glActiveTexture(GL_TEXTURE0 + texSlot));
		GlApiCall(glBindTexture(GL_TEXTURE_2D, m_Id));
	}

	void OpenGLTexture2D::Unbind() const
	{
		GlApiCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		EV_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Buffer size doesn't match width, height, data format.");
		Bind();
		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	}
}

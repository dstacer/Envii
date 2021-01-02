#include "evpch.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "Render/Renderer.h"
#include "OpenGLTexture2D.h"

namespace Envii
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, void* data)
		: m_RendererId(0),
		m_Filepath(""),
		m_Buffer(nullptr),
		m_Width(width),
		m_Height(height),
		m_Channels(0)
	{
		GlApiCall(glGenTextures(1, &m_RendererId));
		Bind();

		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		Unbind();
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_RendererId(0),
		m_Filepath(filepath),
		m_Buffer(nullptr),
		m_Width(0),
		m_Height(0),
		m_Channels(0)
	{
		// data is flipped for .png.  Must set appropriately for other
		// texture formats
		stbi_set_flip_vertically_on_load(true);
		m_Buffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Channels, 4);

		GlApiCall(glGenTextures(1, &m_RendererId));
		Bind();

		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer));
		Unbind();

		if (m_Buffer)
			stbi_image_free(m_Buffer);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		GlApiCall(glDeleteTextures(1, &m_RendererId));
	}

	void OpenGLTexture2D::Bind(unsigned int texSlot) const
	{
		GlApiCall(glActiveTexture(GL_TEXTURE0 + texSlot));
		GlApiCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
	}

	void OpenGLTexture2D::Unbind() const
	{
		GlApiCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{

	}
}

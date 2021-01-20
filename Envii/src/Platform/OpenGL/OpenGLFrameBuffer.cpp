#include "evpch.h"
#include <glad/glad.h>
#include "Render/Renderer.h"
#include "OpenGLFrameBuffer.h"

namespace Envii
{
	static const uint32_t s_MaxFBSize = 8192;
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FbSpecs& specs)
		: m_Specs(specs),
		  m_Id(0)
	{
		Recreate(specs);
	}
	
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		GlApiCall(glDeleteFramebuffers(1, &m_Id));
		GlApiCall(glDeleteTextures(1, &m_ColorAttach));
		GlApiCall(glDeleteTextures(1, &m_DepthAttach));
	}

	void OpenGLFrameBuffer::Bind() const
	{
		GlApiCall(glBindFramebuffer(GL_FRAMEBUFFER, m_Id));
		GlApiCall(glViewport(0, 0, m_Specs.Width, m_Specs.Height));
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		GlApiCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width <= 0 || height <= 0 || width > s_MaxFBSize || height > s_MaxFBSize)
		{
			EV_CORE_WARN("Attempted framebuffer resize to invalid values: {0}, {1}", width, height);
			return;
		}
		m_Specs = { width, height };
		Recreate(m_Specs);
	}

	void OpenGLFrameBuffer::Recreate(const FbSpecs& specs)
	{
		if (m_Id != 0)
		{
			GlApiCall(glDeleteFramebuffers(1, &m_Id));
			GlApiCall(glDeleteTextures(1, &m_ColorAttach));
			GlApiCall(glDeleteTextures(1, &m_DepthAttach));
		}
		
		// Make the color attachment texture 
		GlApiCall(glGenTextures(1, &m_ColorAttach));
		GlApiCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttach));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlApiCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GlApiCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specs.Width, specs.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

		// Make the depth attachment texture
		glGenTextures(1, &m_DepthAttach);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttach);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specs.Width, specs.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		GlApiCall(glGenFramebuffers(1, &m_Id));
		GlApiCall(glBindFramebuffer(GL_FRAMEBUFFER, m_Id));
		GlApiCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttach, 0));
		
		GlApiCall(GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER));
		EV_CORE_ASSERT(status == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete");

		GlApiCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}
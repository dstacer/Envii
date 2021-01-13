#include "evpch.h"
#include "glad/glad.h"
#include "Render/Renderer.h"
#include "OpenGLBuffer.h"

namespace Envii
{
	
	/***************************** VERTEX BUFFER **************************/
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
		: m_Id(0)
	{
		GlApiCall(glGenBuffers(1, &m_Id));
		GlApiCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
		GlApiCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		: m_Id(0)
	{
		GlApiCall(glGenBuffers(1, &m_Id));
		GlApiCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
		GlApiCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GlApiCall(glDeleteBuffers(1, &m_Id));
	}

	void OpenGLVertexBuffer::Bind() const
	{
		GlApiCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		GlApiCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t sizeInBytes)
	{
		GlApiCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id)); 
		GlApiCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeInBytes, data));
	}

	/***************************** INDEX BUFFER **************************/
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Id(0), m_Count(count)
	{
		GlApiCall(glGenBuffers(1, &m_Id));
		GlApiCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
		GlApiCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GlApiCall(glDeleteBuffers(1, &m_Id));
	}

	void OpenGLIndexBuffer::Bind() const
	{
		GlApiCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		GlApiCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}
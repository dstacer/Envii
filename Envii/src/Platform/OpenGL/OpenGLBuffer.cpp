#include "evpch.h"
#include "glad/glad.h"
#include "OpenGLBuffer.h"

namespace Envii
{
	
	/***************************** VERTEX BUFFER **************************/
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		: m_Id(0)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/***************************** INDEX BUFFER **************************/
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Id(0), m_Count(count)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
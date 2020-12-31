#include "evpch.h"

#include <glad/glad.h>
#include "Render/Renderer.h"
#include "OpenGLVertexArray.h"

namespace Envii
{
	GLenum GlTypeFromElement(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;

			EV_CORE_ASSERT(false, "Undefined ShaderDataType: {0}", type);
			return 0;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
		: m_Id(0)
	{
		GlApiCall(glGenVertexArrays(1, &m_Id));
		GlApiCall(glBindVertexArray(m_Id));
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GlApiCall(glDeleteVertexArrays(1, &m_Id));
	}

	void OpenGLVertexArray::Bind() const
	{
		GlApiCall(glBindVertexArray(m_Id));
	}

	void OpenGLVertexArray::Unbind() const
	{
		GlApiCall(glBindVertexArray(0));
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbuf)
	{
		EV_CORE_ASSERT(vbuf->GetLayout().GetElements().size(), "Vertex buffer layout has no elements.");
		
		GlApiCall(glBindVertexArray(m_Id));
		vbuf->Bind();
		const BufferLayout& layout = vbuf->GetLayout();

		uint32_t index = 0;
		for (auto element : layout.GetElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetValueCount(element.Type),
				GlTypeFromElement(element.Type), element.Normalized,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_Vbufs.push_back(vbuf);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibuf)
	{
		GlApiCall(glBindVertexArray(m_Id));
		ibuf->Bind(); 
		
		m_Ibuf = ibuf;
	}
}

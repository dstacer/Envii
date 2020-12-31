#pragma once

#include "Render/VertexArray.h"

namespace Envii
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbuf) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibuf) override;
		
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_Vbufs;
		}

		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override 
		{
			return m_Ibuf;
		}

	private:
		uint32_t m_Id;
		std::vector<std::shared_ptr<VertexBuffer>> m_Vbufs;
		std::shared_ptr<IndexBuffer> m_Ibuf;
	};
}
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
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vbuf) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ibuf) override;
		
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_Vbufs;
		}

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override 
		{
			return m_Ibuf;
		}

	private:
		uint32_t m_Id;
		std::vector<Ref<VertexBuffer>> m_Vbufs;
		Ref<IndexBuffer> m_Ibuf;
	};
}
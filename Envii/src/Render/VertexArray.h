#pragma once

#include <memory>
#include "Buffer.h"

namespace Envii
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vbuf)  = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ibuf) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	private:
		uint32_t m_Id;
	};
}
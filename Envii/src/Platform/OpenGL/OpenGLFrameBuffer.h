#pragma once

#include "Render/FrameBuffer.h"

namespace Envii
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FbSpecs& specs);
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const FbSpecs& GetFrameBufferSpecs() const override { return m_Specs; }
		virtual uint32_t GetColorAttachmentId() const override { return m_ColorAttach; }
		virtual void Resize(uint32_t width, uint32_t height) override 
		{
			m_Specs = { width, height };
			Recreate(m_Specs);
		}

	private:
		void Recreate(const FbSpecs& specs);
	private:
		uint32_t m_Id;
		uint32_t m_ColorAttach;
		uint32_t m_DepthAttach;
		FbSpecs m_Specs;
	};
}
#pragma once

#include "../Core/Core.h"

namespace Envii
{
	struct FbSpecs
	{
		uint32_t Width, Height;
		uint32_t numSamples = 1;
	}; 
	
	class FrameBuffer
	{
	public:
		static Ref<FrameBuffer> Create(const FbSpecs& specs);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const FbSpecs& GetFrameBufferSpecs() const = 0;
		virtual uint32_t GetColorAttachmentId() const = 0;
	};
}
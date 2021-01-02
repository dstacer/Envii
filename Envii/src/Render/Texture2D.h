#pragma once

#include <string>

namespace Envii
{
	class Texture2D
	{
	public:
		virtual ~Texture2D() {}

		virtual void Bind(unsigned int texSlot) const = 0;
		virtual void Unbind() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		static Texture2D* Create(uint32_t width, uint32_t height, void* data);
		static Texture2D* Create(const std::string& filepath);
	};
}

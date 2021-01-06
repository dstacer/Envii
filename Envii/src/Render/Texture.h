#pragma once

#include <string>
#include <vector>

namespace Envii
{
	class Texture
	{
	public:
		virtual ~Texture() {}

		virtual void Bind(uint32_t texSlot = 0) const = 0;
		virtual void Unbind() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, uint32_t numChannels);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, uint32_t numChannels, void* data);
		static Ref<Texture2D> Create(const std::string& filepath, uint32_t texSlot = 0);
	};

	class Texture2DArray : public Texture
	{
	public:
		static Ref<Texture2DArray> Create(const std::vector<std::string> filepaths, uint32_t texSlot = 0);
	};
}

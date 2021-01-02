#pragma once

#include <string>
#include <vector>
namespace Envii
{
	class Texture2DArray
	{

	public:
		virtual ~Texture2DArray() {};

		virtual void Bind(unsigned int texSlot) const = 0;
		virtual void Unbind() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		static Texture2DArray* Create(const std::vector<std::string> filepaths);
	};
}

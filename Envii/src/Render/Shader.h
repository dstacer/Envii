#pragma once

#include <string>
namespace Envii
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
		GEOMETRY = 2,
		NUM_TYPES
	}; 
	
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertSrc, const std::string& fragSrc);
	};
}
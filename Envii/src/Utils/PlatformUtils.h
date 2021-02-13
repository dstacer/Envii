#pragma once

#include <string>

namespace Envii
{
	class FileDialogs
	{
	public:

		// These return an empty string if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);

	private:
	};
}

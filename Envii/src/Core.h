#pragma once

#ifdef EV_PLATFORM_WINDOWS
	#define EV_API
#else
	#error Envii currently only supports Windows.
#endif
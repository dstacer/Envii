#pragma once

#ifdef EV_PLATFORM_WINDOWS
	#define EV_API
#else
	#error Envii currently only supports Windows.
#endif

#define BIT(x) (1 << x)

#ifdef EV_ENABLE_ASSERTS
	#define EV_ASSERT(x, ...) { if (!(x)) { EV_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EV_CORE_ASSERT(x, ...) { if (!(x)) { EV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EV_ASSERT(x, ...)
	#define EV_CORE_ASSERT(x, ...)
#endif
#pragma once

#include <functional>
#include <memory>
#include "Log.h"

#ifdef EV_PLATFORM_WINDOWS
	#define EV_API
#else
	#error Envii currently only supports Windows.
#endif

#define BIT(x) (1 << x)

#ifdef EV_DEBUG
#define EV_ENABLE_ASSERTS
#endif

#ifdef EV_ENABLE_ASSERTS
	#define EV_ASSERT(x, ...) { if (!(x)) { EV_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EV_CORE_ASSERT(x, ...) { if (!(x)) { EV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EV_ASSERT(x, ...)
	#define EV_CORE_ASSERT(x, ...)
#endif

#define EV_BIND_EVENT_CB(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Envii
{
	template<typename T>
	using Scoped = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scoped<T> CreateScoped(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
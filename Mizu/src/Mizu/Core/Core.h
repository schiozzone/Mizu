#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define MZ_PLATFORM_WINDOWS
	#else
		#error "x86 is currently not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is currently not supported"
	#elif TARGET_OS_IPHONE == 1
		#define MZ_PLATFORM_IOS
		#error "IOS is currently not supported"
	#elif TARGET_OS_MAC == 1
		#define MZ_PLATFORM_MACOS
		#error "MacOS is currently not supported"
	#else
		#error "Unknown Apple platform"
	#endif
#elif defined(__ANDROID__)
	#define MZ_PLATFORM_ANDROID
	#error "Android is currently not supported"
#elif defined(__linux__)
	#define MZ_PLATFORM_LINUX
#error "Linux is currently not supported"
#else
	#error "Unknown platform
#endif

#ifdef MZ_DEBUG
	#define MZ_ENABLE_ASSERTS
#endif

#ifdef MZ_ENABLE_ASSERTS
	#define MZ_ASSERT(x, ...) { if(!(x)) { MZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MZ_CORE_ASSERT(x, ...) { if(!(x)) { MZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MZ_ASSERT(x, ...)
	#define MZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MZ_BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)

namespace Mizu {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
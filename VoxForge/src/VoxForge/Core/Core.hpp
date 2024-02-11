#pragma once

#include <memory>

#define VF_DEBUGBREAK() __debugbreak()

#define VOX_BUILD_ID "v.0.0.1"

namespace VoxForge
{
	// Unique ptr wrapper
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Shared ptr wrapper
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "VoxForge/Core/Debug/Log.hpp"
#include "VoxForge/Core/Debug/Assert.hpp"

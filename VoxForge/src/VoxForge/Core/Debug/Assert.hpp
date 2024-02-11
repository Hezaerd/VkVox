#pragma once

#include "VoxForge/Core/Core.hpp"
#include "VoxForge/Core/Debug/Log.hpp"

#ifdef VF_DEBUG
	#define VF_ENABLE_ASSERTS
#endif

#ifdef VF_ENABLE_ASSERTS
	#define VF_ASSERT_MESSAGE_INTERNAL(...) ::VoxForge::Log::PrintAssertMessage(::VoxForge::Log::Type::Forge, "Assertion failed" __VA_OPT__(,) __VA_ARGS__)
	#define VS_ASSERT_MESSAGE_INTERNAL(...) ::VoxForge::Log::PrintAssertMessage(::VoxForge::Log::Type::Studio, "Assertion failed" __VA_OPT__(,) __VA_ARGS__)

	#define VF_ASSERT(condition, ...) {if(!(condition)) { VF_ASSERT_MESSAGE_INTERNAL(__VA_ARGS__); VF_DEBUGBREAK(); }}
	#define VS_ASSERT(condition, ...) {if(!(condition)) { VS_ASSERT_MESSAGE_INTERNAL(__VA_ARGS__); VF_DEBUGBREAK(); }}
#else
	#define VF_ASSERT(condition, ...)
	#define VS_ASSERT(condition, ...)
#endif

#pragma once

#include "VoxForge/Core/Core.hpp"
#include "VoxForge/Core/Debug/Log.hpp"

// Verify are just like asserts, but instead of passing it an expression,
// you pass it a condition directly.

// Example :
// VF_ASSERT(false, "This should break!");
// VF_VERIFY((true == false), "This should break!");

#ifdef VF_DEBUG
	#define VF_ENABLE_VERIFY
#endif

#ifdef VF_ENABLE_ASSERTS
	#define VF_VERIFY_MESSAGE_INTERNAL(...) ::VoxForge::Log::PrintAssertMessage(::VoxForge::Log::Type::Forge, "Verify failed" __VA_OPT__(,) __VA_ARGS__)
	#define VS_VERIFY_MESSAGE_INTERNAL(...) ::VoxForge::Log::PrintAssertMessage(::VoxForge::Log::Type::Studio, "Verify failed" __VA_OPT__(,) __VA_ARGS__)
	
	#define VF_VERIFY(condition, ...) {if(!(condition)) { VF_VERIFY_MESSAGE_INTERNAL(__VA_ARGS__); VF_DEBUGBREAK(); }}
	#define VS_VERIFY(condition, ...) {if(!(condition)) { VS_VERIFY_MESSAGE_INTERNAL(__VA_ARGS__); VF_DEBUGBREAK(); }}
#else
	#define VF_VERIFY(condition, ...)
	#define VS_VERIFY(condition, ...)
#endif



#include "vfpch.hpp"
#include "VoxForge/Core/Core.hpp"

#include "VoxForge/Core/Debug/Log.hpp"

#define VOX_BUILD_ID "v.0.0.1a"

namespace VoxForge
{
	void InitCore()
	{
		Log::Init();

		VF_TRACE_TAG("Core", "Log System Initialized!");
		VF_TRACE_TAG("Core", "VoxForge Engine Build ID: {0}", VOX_BUILD_ID);
		VF_TRACE_TAG("Core", "Initializing...");
	}

	void ShutdownCore()
	{
		VF_TRACE_TAG("Core", "Shutting down...");

		Log::Shutdown();
	}
}

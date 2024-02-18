#pragma once

#include "VoxForge/Core/Application.hpp"

// Client entry Point
extern VoxForge::Application* VoxForge::CreateApplication(int argc, char** argv); // NOTE: this is defined in the CLIENT

// apllication running flag
inline bool g_ApplicationRunning = true;

namespace VoxForge
{
	int Main(int argc, char** argv)
	{
		while(g_ApplicationRunning)
		{
			InitCore();

			Application* app = CreateApplication(argc, argv);
			VF_ASSERT(app, "Studio application is null!")
			app->Run();
			delete app;

			ShutdownCore();
		}
		return 0;
	}
}

inline int main(int argc, char** argv)
{
	return VoxForge::Main(argc, argv);
}

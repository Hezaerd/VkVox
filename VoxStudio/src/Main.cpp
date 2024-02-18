#include <VoxForge.hpp>

int main()
{
	VoxForge::Log::Init();
	
	VS_INFO("Entry Point!");

	VoxForge::WindowSpecification windowSpecs;
	windowSpecs.Title = "VoxStudio";
	windowSpecs.Width = 1280;
	windowSpecs.Height = 720;

	const auto window = VoxForge::Window::Create(windowSpecs);
	window->Init();
	window->CenterWindow();

	while (true)
	{
	}

	VoxForge::Log::Shutdown();
}


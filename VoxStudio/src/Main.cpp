#include <VoxForge.hpp>

int main()
{
	VoxForge::Log::Init();
	
	VS_INFO("Entry Point!");

	VoxForge::ApplicationSpecification appSpec;
	appSpec.Title = "VoxForge";
	appSpec.WindowWidth = 1280;
	appSpec.WindowHeight = 720;

	auto app = VoxForge::Application::CreateApplication(appSpec);
	app->Run();
	
	VoxForge::Log::Shutdown();
}


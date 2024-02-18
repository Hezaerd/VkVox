#include <VoxForge.hpp>

class VoxStudio : public VoxForge::Application
{
public:
	VoxStudio(const VoxForge::ApplicationSpecification& pSpec)
		: VoxForge::Application(pSpec)
	{
	}
};

VoxForge::Application* VoxForge::CreateApplication(int argc, char** argv)
{
	VoxForge::ApplicationSpecification spec;
	spec.Title = "Vox Studio";
	spec.WindowWidth = 1280;
	spec.WindowHeight = 720;
	spec.VSync = true;
	spec.FullScreen = false;
	spec.Resizable = true;

	return new VoxStudio(spec);
}

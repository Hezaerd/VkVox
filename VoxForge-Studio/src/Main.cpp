#include <VoxForge.hpp>

bool CrashingFunction()
{
	return false;
}

int main()
{
	VoxForge::Log::Init();
	
	VS_INFO("Entry Point!");

	// Test variables in log
	int a = 5;
	VF_INFO("Hello! Var={0}", a);

	// test asserts - should not break
	VF_ASSERT(true, "This should not break!")
	
	// test asserts - should break
	VF_ASSERT(CrashingFunction(), "Crashing function failed!")

	while (true)
	{
		
	}

	VoxForge::Log::Shutdown();
}


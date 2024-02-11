#include <VoxForge.hpp>

int main()
{
	VoxForge::Log::Init();
	
	VS_INFO("Entry Point!");

	// Test variables in log
	int a = 5;
	VS_INFO("Hello! Var={0}", a);

	// test asserts - should not break
	VS_ASSERT(true, "This should not break!")

	// test verify - should not break
	VS_VERIFY((true == true), "This should not break!")
	
	// test asserts - should break
	VS_ASSERT(false, "This should break!")

	// test verify - should break
	VS_VERIFY((true == false), "This should break!")

	while (true)
	{
		
	}

	VoxForge::Log::Shutdown();
}


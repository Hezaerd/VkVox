#include "vfpch.hpp"
#include "Application.hpp"

// apllication running flag
bool g_ApplicationRunning = true;

namespace VoxForge
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& pSpec)
	{
		VF_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;
		
		m_Spec = pSpec;

		WindowSpecification windowSpecs;
		windowSpecs.Title = pSpec.Title;
		windowSpecs.Width = pSpec.WindowWidth;
		windowSpecs.Height = pSpec.WindowHeight;
		windowSpecs.VSync = pSpec.VSync;
		windowSpecs.FullScreen = pSpec.FullScreen;

		m_Window = Window::Create(windowSpecs);
		m_Window->Init();

		m_Window->CenterWindow();
		m_Window->SetResizable(pSpec.Resizable);
	}

	Application::~Application()
	{
	}

	Application* Application::CreateApplication(const ApplicationSpecification& pSpec)
	{
		return new Application(pSpec);
	}

	void Application::Run()
	{
		OnInit();

		while (m_Running)
		{
			ProcessEvents();
			OnUpdate();
		}

		OnShutdown();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnShutdown()
	{
		g_ApplicationRunning = false;
	}

	void Application::ProcessEvents()
	{
		m_Window->ProcessEvents();
	}

	float Application::GetTime()
	{
		return (float)glfwGetTime();
	}
}

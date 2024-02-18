#pragma once

#include "VoxForge/Core/Core.hpp"

#include "VoxForge/Core/Window.hpp"

namespace VoxForge
{
	struct ApplicationSpecification
	{
		std::string Title;
		uint32_t WindowWidth;
		uint32_t WindowHeight;

		bool VSync = true;
		bool FullScreen = false;
		
		bool Resizable = true;
	};
	
	class Application
	{
	public:
		Application(const ApplicationSpecification& pSpec);
		virtual ~Application();

		void Run();
		void Close();

		void OnInit() { }
		void OnShutdown();
		void OnUpdate() { }

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }

		float GetTime();

	public:
		static Application* CreateApplication(const ApplicationSpecification& pSpec);
	
	private:
		void ProcessEvents();

	private:
		ApplicationSpecification m_Spec;
		Scope<Window> m_Window;

		bool m_Running = true;
		bool m_Minimized = false;

	private:
		static Application* s_Instance;
	};
}

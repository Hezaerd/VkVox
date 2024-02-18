#pragma once
#include "VoxForge/Core/Core.hpp"
#include <GLFW/glfw3.h>

namespace VoxForge
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		bool VSync = true;
		bool FullScreen = false;
	};
	
	class Window
	{
	public:
		Window(const WindowSpecification& pProps);
		~Window();

		void Init();
		void ProcessEvents() const;
		void SwapBuffers() const;
		
		uint32_t GetWidth() const { return m_Data.Width; }
		uint32_t GetHeight() const { return m_Data.Height; }
		std::pair<uint32_t, uint32_t> GetSize() const { return { m_Data.Width, m_Data.Height }; }
		
		std::pair<float, float> GetPosition() const;
		void SetPosition(int pX, int pY) const;

		// Window attributes
		void SetVSync(bool pEnabled);
		bool IsVSync() const;
		void SetResizable(bool pEnabled);

		void Maximize() const;
		void Minimize() const;
		void CenterWindow() const;

		const std::string& GetTitle() const { return m_Data.Title; }
		void SetTitle(const std::string& pTitle);

		inline void* GetNativeWindow() const { return m_Window; }

	public:
		static Scope<Window> Create(const WindowSpecification& pProps);

	private:
		void Shutdown();
		
	private:
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
		};

		WindowData m_Data;
		WindowSpecification m_Specification;
		
	private:
		GLFWwindow* m_Window;
	};
}

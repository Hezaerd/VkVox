#include "vfpch.hpp"
#include "VoxForge/Core/Window.hpp"

namespace VoxForge
{
	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int pError, const char* pDescription)
	{
		VF_ERROR_TAG("GLFW", "GLFW Error ({0}): {1}", pError, pDescription);
	}

	Scope<Window> Window::Create(const WindowSpecification& pSpecs)
	{
		return CreateScope<Window>(pSpecs);
	}

	Window::Window(const WindowSpecification& pSpecs)
	{
		m_Specification = pSpecs;
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init()
	{
		m_Data.Title = m_Specification.Title;
		m_Data.Width = m_Specification.Width;
		m_Data.Height = m_Specification.Height;

		VF_INFO_TAG("GLFW", "Creating window {0} ({1}, {2})", m_Specification.Title, m_Specification.Width, m_Specification.Height);

		if (!s_GLFWInitialized)
		{
			const int success = glfwInit();
			VF_ASSERT(success, "Could not initialize GLFW!")
			glfwSetErrorCallback(GLFWErrorCallback);
			
			s_GLFWInitialized = true;
		}

		if (m_Specification.FullScreen)
		{
			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
			
			
			glfwWindowHint(GLFW_DECORATED, false);
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

			m_Window = glfwCreateWindow(mode->width, mode->height, m_Data.Title.c_str(), primaryMonitor, nullptr);
		}
		else
		{
			m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		}
		
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		else
			VF_WARN_TAG("GLFW", "Raw mouse motion is not supported on this system!");
	}

	void Window::Shutdown()
	{
		glfwTerminate();
		s_GLFWInitialized = false;
	}

	std::pair<float, float> Window::GetPosition() const
	{
		int x, y;
		glfwGetWindowPos(m_Window, &x, &y);
		return { (float)x, (float)y };
	}

	void Window::SetPosition(const int pX, const int pY) const
	{
		VF_ASSERT(m_Window, "Window is not initialized!")
		
		glfwSetWindowPos(m_Window, (int)pX, (int)pY);
	}

	void Window::ProcessEvents() const
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool pEnabled)
	{
		VF_ASSERT(m_Window, "Window is not initialized!")
		
		if (pEnabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Specification.VSync = pEnabled;
	}

	bool Window::IsVSync() const
	{
		return m_Specification.VSync;
	}

	void Window::SetResizable(const bool pEnabled)
	{
		VF_ASSERT(m_Window, "Window is not initialized!")
		
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, pEnabled);
	}

	void Window::Maximize() const
	{
		VF_ASSERT(m_Window, "Window is not initialized!")
		
		glfwMaximizeWindow(m_Window);
	}

	void Window::Minimize() const
	{
		VF_ASSERT(m_Window, "Window is not initialized!")
		
		glfwIconifyWindow(m_Window);
	}

	void Window::CenterWindow() const
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		const int x = (mode->width - m_Data.Width) / 2;
		const int y = (mode->height - m_Data.Height) / 2;

		SetPosition(x, y);
	}

	void Window::SetTitle(const std::string& pTitle)
	{
		VF_ASSERT(m_Window, "Window is not initialized!")
		
		m_Data.Title = pTitle;
		glfwSetWindowTitle(m_Window, pTitle.c_str());
	}
}

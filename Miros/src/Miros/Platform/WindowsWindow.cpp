//#define  MRS_ENABLE_ASSERTS

#include "../Core.h"
#include "WindowsWindow.h"
#include "../Log.h"
#include "../Events/AppicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/Event.h"

#include "glad/glad.h"

namespace Miros {


	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		MRS_CORE_ERROR("GLFW Error ({0}) : {1}", error, description);
	}

	Window* Miros::Window::Create(const WindowProps& props /*= WindowProps()*/)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MRS_CORE_INFO("Create window {0} {1} {2}", props.Title, props.Width, props.Height);
		
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			MRS_CORE_ASSERT(success, "Could not initialize GLFW!");
			//?󶨴????ص?????
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int heigh) 
			{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

			WindowResizeEvent e(width, heigh);
			data.Width = width;
			data.Height = heigh;
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int key,int scancode,int action,int modes)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent e(key, 0);
				data.EventCallback(e);
				break;
			}

			case GLFW_RELEASE: {
				KeyReleasedEvent e(key);
				data.EventCallback(e);
				break;
			}

			case GLFW_REPEAT: {
				KeyPressedEvent e(key, 1);
				data.EventCallback(e);
				break;
			}

			}

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
			case GLFW_PRESS: {
				MouseButtonPressedEvent e(button);
				data.EventCallback(e);
				break;
			}

			case GLFW_RELEASE: {
				MouseButtonReleasedEvent e(button);
				data.EventCallback(e);
				break;}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xOffset, (float)yOffset);

			data.EventCallback(e);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float)xPos, (float)yPos);
			data.EventCallback(e);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
#include "evpch.h"
#include "Events/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "WindowsWindow.h"

namespace Envii
{
	static bool s_GlfwInitialized = false;

	static void glfwErrorCB(int error, const char* desc)
	{
		EV_CORE_ERROR("GLFW Error: ({0}) {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props)
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

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EV_CORE_INFO("Creating Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GlfwInitialized)
		{
			// TODO: glfwTerminate at shutdown
			bool success = glfwInit();
			EV_CORE_ASSERT(success, "Failed to initialize GLFW.");

			glfwSetErrorCallback(glfwErrorCB);

			s_GlfwInitialized = true;
		}

		// Create GLFW window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, 
									props.Title.c_str(), nullptr, nullptr);
		
		// Get our graphics context
		glfwMakeContextCurrent(m_Window);

		// Load OpenGL procs
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EV_CORE_ASSERT(status, "GLAD failed to load GL lib.");

		// Supply the GLFW window with a pointer to our internal data struct
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set the GLFW event callbacks for window events
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.Callback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.Callback(e);
		});

		// Set the GLFW event callbacks for keyboard events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent event(key, 0);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent event(key);
					data.Callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent event(key, 1);
					data.Callback(event);
					break;
				}
			}
		});

		// Set the GLFW event callbacks for keyboard events
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keyCode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keyCode);
			data.Callback(event);
		});

		// Set the GLFW event callbacks for mouse events
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent event(button);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent event(button);
					data.Callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xDist, double yDist)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event((float)xDist, (float)yDist);
			data.Callback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float)xPos, (float)yPos);
			data.Callback(event);
		});
	}
	
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
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

	

	
}
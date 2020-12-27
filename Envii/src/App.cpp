#include "evpch.h"

#include "GLFW/glfw3.h"
#include "Log.h"
#include "App.h"

namespace Envii
{
	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	App::~App()
	{
	}
	
	void App::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
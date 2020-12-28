#include "evpch.h"

#include "glad/glad.h"
#include "Log.h"
#include "App.h"

namespace Envii
{
#define BIND_EVENT_CB(x) std::bind(&x, this, std::placeholders::_1)
	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_CB(App::OnEvent));
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

			// Update all the layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update our main window
			m_Window->OnUpdate();
		}
	}

	void App::OnEvent(Event& event)
	{
		EventDispatcher d(event);
		d.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(App::OnWindowClose));
		
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_handled)
				break;
			(*it)->OnEvent(event);
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
	
	bool App::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}
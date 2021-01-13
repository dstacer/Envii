#include "evpch.h"

#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Log.h"
#include "App.h"
#include "Input.h"
#include "Timestep.h"
#include "Profiler.h"
#include "Render/Renderer.h"

// Temporary - needs to be platform-independent
#include <GLFW/glfw3.h>

namespace Envii
{	
	App* App::s_Instance = nullptr;
	App::App()
	{
		EV_CORE_ASSERT(!s_Instance, "App already exists.");
		s_Instance = this;

		// Make our window (single window for now)
		m_Window =  Scoped<Window>(Window::Create());
		m_Window->SetEventCallback(EV_BIND_EVENT_CB(App::OnEvent));

		// Init Renderer - currently just sets blending options
		Renderer::Init();

		// Make our ImguiLayer for UI stuff
		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);
	}

	App::~App()
	{
	}
	
	void App::Run()
	{
		EV_PROFILE_BEGIN_SESSION("EnviiApp"); 
		while (m_Running)
		{
			EV_PROFILE_SCOPE("App Run");
			float time = (float)glfwGetTime();
			TimeStep elapsedTime(time - m_LastFrameTime);
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				// Update all the layers
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(elapsedTime);
			}

			// Do Imgui rendering for all the layers.
			m_ImguiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImguiRender();
			m_ImguiLayer->End();
		
			// Update our main window
			m_Window->OnUpdate();
		}
		EV_PROFILE_END_SESSION();
		Renderer::Shutdown();
	}

	void App::OnEvent(Event& event)
	{
		EventDispatcher d(event);
		d.Dispatch<WindowCloseEvent>(EV_BIND_EVENT_CB(App::OnWindowClose));
		d.Dispatch<WindowResizeEvent>(EV_BIND_EVENT_CB(App::OnWindowResize));
		
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_handled)
				break;
			(*it)->OnEvent(event);
		}
	}

	void App::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_LayerStack.PushLayer(layer);
		
	}

	void App::PushOverlay(Layer* overlay)
	{
		overlay->OnAttach(); 
		m_LayerStack.PushOverlay(overlay);
	}
	
	bool App::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}
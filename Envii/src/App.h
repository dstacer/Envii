#pragma once

#include "LayerStack.h"
#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"

namespace Envii
{
	class App
	{
	public:	
		App();
		virtual ~App();

		void Run();
		void OnEvent(Event& event);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// Client must define this function to create their own Envii::App
	App* CreateApp();
}


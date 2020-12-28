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

		inline Window& GetWindow() { return *m_Window; }
		inline static App& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static App* s_Instance;
	};

	// Client must define this function to create their own Envii::App
	App* CreateApp();
}


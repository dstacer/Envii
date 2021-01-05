#pragma once

#include "LayerStack.h"
#include "Core.h"
#include "Window.h"
#include "../Events/AppEvent.h"
#include "../Imgui/ImguiLayer.h"
#include "../Render/VertexArray.h"
#include "../Render/Buffer.h"
#include "../Render/Shader.h"
#include "../Render/OrthoCamera.h"

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
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		Scoped<Window> m_Window;
		ImguiLayer* m_ImguiLayer;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static App* s_Instance;
		bool m_Running = true;
		bool m_Minimized = false;
	};

	// Client must define this function to create their own Envii::App
	App* CreateApp();
}

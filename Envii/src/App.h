#pragma once

#include "LayerStack.h"
#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "Imgui/ImguiLayer.h"
#include "Render/VertexArray.h"
#include "Render/Buffer.h"
#include "Render/Shader.h"

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
		ImguiLayer* m_ImguiLayer;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_TriVao;
		std::shared_ptr<VertexArray> m_QuadVao;

		std::shared_ptr<Shader> m_TriShader;
		std::shared_ptr<Shader> m_QuadShader;

		static App* s_Instance;
		bool m_Running = true;
	};

	// Client must define this function to create their own Envii::App
	App* CreateApp();
}


#include "evpch.h"

#include "Log.h"
#include "App.h"
#include "Core.h"
#include "Input.h"
#include "Render/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Envii
{	
	App* App::s_Instance = nullptr;
	App::App()
	{
		EV_CORE_ASSERT(!s_Instance, "App already exists.");
		s_Instance = this;

		// Make our window (single window for now)
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EV_BIND_EVENT_CB(App::OnEvent));

		// Make our ImguiLayer for UI stuff
		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);

		float vertices[] = {  
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		// Create vertex array
		m_TriVao.reset( VertexArray::Create() );

		// Create vertex buffer and layout
		std::shared_ptr<VertexBuffer> triVb;
		triVb.reset( VertexBuffer::Create(vertices, sizeof(vertices)) );
		triVb->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Color" }
		});
		
		// Create index buffer
		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> triIb;
		triIb.reset( IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)) );

		m_TriVao->AddVertexBuffer(triVb);
		m_TriVao->SetIndexBuffer(triIb);

		float quadVertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		// Create vertex array
		m_QuadVao.reset( VertexArray::Create() );

		// Create vertex buffer and layout
		std::shared_ptr<VertexBuffer> quadVb;
		quadVb.reset( VertexBuffer::Create(quadVertices, sizeof(quadVertices)) );
		quadVb->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
		});

		// Create index buffer
		uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> quadIb;
		quadIb.reset( IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)) );

		m_QuadVao->AddVertexBuffer(quadVb);
		m_QuadVao->SetIndexBuffer(quadIb);

		// Create camera
		m_Camera.reset(new OrthoCamera(glm::ortho(-3.2f, 3.2f, -1.8f, 1.8f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

		// Create shaders
		std::string vertSrc = 
		R"(#version 330 core

		layout (location = 0) in vec4 a_Pos;
		layout (location = 1) in vec4 a_Color;

		out vec4 v_Color;
		uniform mat4 u_MVP;

		void main()
		{
			gl_Position = u_MVP * a_Pos;
			v_Color = a_Color;
		})";

		std::string fragSrc = 
		R"(#version 330 core

		layout (location = 0) out vec4 color;
		in vec4 v_Color;

		void main()
		{
			color = v_Color;
		})";

		m_TriShader.reset( Shader::Create(vertSrc, fragSrc) );
		m_TriShader->Bind();

		std::string quadVertSrc =
			R"(#version 330 core

		layout (location = 0) in vec3 a_Pos;
		out vec3 v_pos;
		uniform mat4 u_MVP;

		void main()
		{
			gl_Position = u_MVP * vec4(a_Pos, 1.0);
			v_pos = a_Pos;
		})";

		std::string quadFragSrc =
			R"(#version 330 core

		layout (location = 0) out vec4 color;
		in vec3 v_pos;
		void main()
		{
			color = vec4(v_pos * 0.5 + 0.5, 1.0);
		})";

		m_QuadShader.reset(Shader::Create(quadVertSrc, quadFragSrc));
		m_QuadShader->Bind();
	}

	App::~App()
	{
	}
	
	void App::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor( { 0.4f, 0.4f, 0.4f, 1.0f } );
			RenderCommand::Clear();
			
			m_Camera->SetRotation(45.f);
			m_Camera->SetPosition(glm::vec3(0.5f, 0.5f, 0.0f));
			Renderer::BeginScene(*m_Camera);

			Renderer::Submit(m_QuadVao, m_QuadShader);
			Renderer::Submit(m_TriVao, m_TriShader);

			Renderer::EndScene();
			
			// Update all the layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Do Imgui rendering for all the layers.
			m_ImguiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImguiRender();
			m_ImguiLayer->End();

			// Update our main window
			m_Window->OnUpdate();
		}
	}

	void App::OnEvent(Event& event)
	{
		EventDispatcher d(event);
		d.Dispatch<WindowCloseEvent>(EV_BIND_EVENT_CB(App::OnWindowClose));
		
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
}
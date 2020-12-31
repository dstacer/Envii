#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TestLayer.h"
#include "imgui.h"

TestLayer::TestLayer()
	: Envii::Layer("TestLayer"), m_TriPos(glm::vec3(0.f)), m_QuadPos(glm::vec3(0.f))
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	};

	// Create vertex array
	m_TriVao.reset(Envii::VertexArray::Create());

	// Create vertex buffer and layout
	std::shared_ptr<Envii::VertexBuffer> triVb;
	triVb.reset(Envii::VertexBuffer::Create(vertices, sizeof(vertices)));
	triVb->SetLayout({
		{ Envii::ShaderDataType::Float3, "a_Pos" },
		{ Envii::ShaderDataType::Float4, "a_Color" }
		});

	// Create index buffer
	uint32_t indices[] = { 0, 1, 2 };
	std::shared_ptr<Envii::IndexBuffer> triIb;
	triIb.reset(Envii::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	m_TriVao->AddVertexBuffer(triVb);
	m_TriVao->SetIndexBuffer(triIb);

	float quadVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	// Create vertex array
	m_QuadVao.reset(Envii::VertexArray::Create());

	// Create vertex buffer and layout
	std::shared_ptr<Envii::VertexBuffer> quadVb;
	quadVb.reset(Envii::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
	quadVb->SetLayout({
		{ Envii::ShaderDataType::Float3, "a_Pos" },
		});

	// Create index buffer
	uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Envii::IndexBuffer> quadIb;
	quadIb.reset(Envii::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));

	m_QuadVao->AddVertexBuffer(quadVb);
	m_QuadVao->SetIndexBuffer(quadIb);

	// Create camera
	m_Camera.reset(new Envii::OrthoCamera(glm::ortho(-3.2f, 3.2f, -1.8f, 1.8f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

	// Create shaders
	std::string vertSrc =
		R"(#version 330 core

		layout (location = 0) in vec4 a_Pos;
		layout (location = 1) in vec4 a_Color;

		out vec4 v_Color;
		uniform mat4 u_VP;
		uniform mat4 u_Transform;

		void main()
		{
			gl_Position = u_VP * u_Transform * a_Pos;
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

	m_TriShader.reset(Envii::Shader::Create(vertSrc, fragSrc));
	m_TriShader->Bind();

	std::string quadVertSrc =
		R"(#version 330 core

		layout (location = 0) in vec3 a_Pos;
		out vec3 v_pos;
		uniform mat4 u_VP;
		uniform mat4 u_Transform;

		void main()
		{
			gl_Position = u_VP * u_Transform * vec4(a_Pos, 1.0);
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

	m_QuadShader.reset(Envii::Shader::Create(quadVertSrc, quadFragSrc));
	m_QuadShader->Bind();
}

void TestLayer::OnUpdate(Envii::TimeStep ts)
{
	// Object positions
	glm::mat4 triMat(glm::translate(glm::mat4(1.0), m_TriPos));

	// User Camera Translation
	if (Envii::Input::IsKeyPressed(EV_KEY_LEFT))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(-6.f * ts, 0.f, 0.f));
	}
	else if (Envii::Input::IsKeyPressed(EV_KEY_RIGHT))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(6.f * ts, 0.f, 0.f));
	}
	else if (Envii::Input::IsKeyPressed(EV_KEY_UP))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.f, 6.f * ts, 0.f));
	}
	else if (Envii::Input::IsKeyPressed(EV_KEY_DOWN))
	{
		m_Camera->SetPosition(m_Camera->GetPosition() + glm::vec3(0.f, -6.f * ts, 0.f));
	}

	// User Camera Rotation
	if (Envii::Input::IsKeyPressed(EV_KEY_D))
	{
		m_Camera->SetRotation(m_Camera->GetRotation() - 360.f * ts);
	}
	else if (Envii::Input::IsKeyPressed(EV_KEY_F))
	{
		m_Camera->SetRotation(m_Camera->GetRotation() + 360.f * ts);
	}
	
	Envii::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1.0f });
	Envii::RenderCommand::Clear();

	Envii::Renderer::BeginScene(*m_Camera);
	glm::mat4 scale = glm::scale(glm::mat4(1.f), { 0.1f, 0.1f, 0.1f } );
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 40; x++)
		{
			glm::vec3 pos = { 0.1f * x, 0.1 * y, 0.0f };
			glm::mat4 trans = glm::translate(glm::mat4(1.f), pos) * scale;
			Envii::Renderer::Submit(m_QuadVao, m_QuadShader, trans);
		}
	}
	
	Envii::Renderer::Submit(m_TriVao, m_TriShader, triMat);

	Envii::Renderer::EndScene();
}

void TestLayer::OnImguiRender()
{
	ImGui::Begin("Sandbox Imgui Test");
	ImGui::DragFloat3("Tri Position:", glm::value_ptr(m_TriPos));
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void TestLayer::OnEvent(Envii::Event& event) 
{
	Envii::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Envii::KeyPressEvent>(EV_BIND_EVENT_CB(TestLayer::OnKeyPressEvent));
}

bool TestLayer::OnKeyPressEvent(Envii::KeyPressEvent& event)
{
	return false;
}

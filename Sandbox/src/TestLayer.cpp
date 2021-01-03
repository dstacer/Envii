#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TestLayer.h"
#include "imgui.h"

TestLayer::TestLayer()
	: Envii::Layer("TestLayer"), 
	  m_Pos(glm::vec3(0.f)), 
	  m_SquarePos(glm::vec3(0.f)),
	  m_CamCtl(1.778f)
{
	float vertices[] = {
		-0.6f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.6f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		 0.6f,  0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.6f,  0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	// Create vertex array
	m_Vao = Envii::VertexArray::Create();

	// Create vertex buffer and layout
	Envii::Ref<Envii::VertexBuffer> Vb;
	Vb = Envii::VertexBuffer::Create(vertices, sizeof(vertices));
	Vb->SetLayout({
		{ Envii::ShaderDataType::Float3, "a_Pos" },
		{ Envii::ShaderDataType::Float4, "a_Color" },
		{ Envii::ShaderDataType::Float2, "a_TexCoord" }
	});

	// Create index buffer
	uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
	Envii::Ref<Envii::IndexBuffer> Ib;
	Ib = Envii::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_Vao->AddVertexBuffer(Vb);
	m_Vao->SetIndexBuffer(Ib);

	float quadVertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	// Create vertex array
	m_SquareVao = Envii::VertexArray::Create();

	// Create vertex buffer and layout
	Envii::Ref<Envii::VertexBuffer> quadVb;
	quadVb = Envii::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	quadVb->SetLayout({
		{ Envii::ShaderDataType::Float3, "a_Pos" },
		{ Envii::ShaderDataType::Float2, "a_TexCoord" }
	});

	// Create index buffer
	uint32_t quadIndices[] = { 0, 1, 2, 2, 3, 0 };
	Envii::Ref<Envii::IndexBuffer> quadIb;
	quadIb = Envii::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));

	m_SquareVao->AddVertexBuffer(quadVb);
	m_SquareVao->SetIndexBuffer(quadIb);

	// Create shaders
	m_ShaderLib.Load("assets/shaders/Square.glsl");
	m_ShaderLib.Load("assets/shaders/Quad.glsl");

	m_Tex = Envii::Texture2D::Create("assets/textures/Kreator.png", 0);
	m_Tex->Bind(0);
	m_SquareTex = Envii::Texture2D::Create("assets/textures/Checkerboard.png", 1);
	m_SquareTex->Bind(1);
}

void TestLayer::OnUpdate(Envii::TimeStep ts)
{
	// Object positions
	glm::mat4 Mat(glm::translate(glm::mat4(1.0), m_Pos));

	m_CamCtl.OnUpdate(ts);
	
	Envii::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1.0f });
	Envii::RenderCommand::Clear();

	Envii::Renderer::BeginScene(m_CamCtl.GetCamera());
	glm::mat4 scale = glm::scale(glm::mat4(1.f), { 0.2f, 0.2f, 0.2f } );

	Envii::Ref<Envii::Shader> squareShader = m_ShaderLib.Get("Square");
	squareShader->Bind();
	squareShader->SetUniform1i("u_TexSlot", 1);
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos = { 0.205f * x, 0.205 * y, 0.0f };
			glm::mat4 trans = glm::translate(glm::mat4(1.f), pos) * scale;
			Envii::Renderer::Submit(m_SquareVao, squareShader, trans);
		}
	}
	
	Envii::Ref<Envii::Shader> quadShader = m_ShaderLib.Get("Quad");
	quadShader->Bind();
	quadShader->SetUniform1i("u_TexSlot", 0);
	Envii::Renderer::Submit(m_Vao, quadShader, Mat);

	Envii::Renderer::EndScene();
}

void TestLayer::OnImguiRender()
{
	ImGui::Begin("Sandbox Imgui Test");
	ImGui::SliderFloat3("Quad Position:", glm::value_ptr(m_Pos),-2.f, 2.f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void TestLayer::OnEvent(Envii::Event& event) 
{
	m_CamCtl.OnEvent(event);

	Envii::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Envii::KeyPressEvent>(EV_BIND_EVENT_CB(TestLayer::OnKeyPressEvent));
}

bool TestLayer::OnKeyPressEvent(Envii::KeyPressEvent& event)
{
	return false;
}

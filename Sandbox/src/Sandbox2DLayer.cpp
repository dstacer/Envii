#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "Sandbox2DLayer.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Envii::Layer("Sandbox2DLayer"), 
	  m_CamCtl(1.778f)
{
	
}

Sandbox2DLayer::~Sandbox2DLayer()
{
	
}

void Sandbox2DLayer::OnAttach()
{
	m_Tex = Envii::Texture2D::Create("assets/textures/Kreator.png", 1);
	m_SquareTex = Envii::Texture2D::Create("assets/textures/Checkerboard.png", 2);
	m_SpriteSheet = Envii::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png", 3);
	m_StairsTex = Envii::SubTexture2D::CreateFromIndices(m_SpriteSheet, glm::vec2(2.f, 1.f), 128.f, glm::vec2(1, 2));
}

void Sandbox2DLayer::OnDetach()
{
	
}

void Sandbox2DLayer::OnUpdate(Envii::TimeStep ts)
{
	EV_PROFILE_FUNCTION();

	m_CamCtl.OnUpdate(ts);

	Envii::Renderer2D::ResetStats();
	
	Envii::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Envii::RenderCommand::Clear();
	
#if 0
	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());
	
	Envii::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 10.0f, 10.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_SquareTex, 4.0f, 1);
	for (float x = -10.0f; x < 10.0f; x += 0.1f)
	{
		for (float y = -10.0f; y < 10.0f; y += 0.1f)
		{
			glm::vec4 color = { (x + 6.0f) / 12.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
			Envii::Renderer2D::DrawQuad({ x, y, -0.15f }, { 0.08, 0.08 }, color);
		}
	}
	Envii::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 3.0f, 1.25f }, { 0.1f, 0.2f, 0.8f, 1.0f });
	Envii::Renderer2D::DrawQuadRotate({ 0.0f, 0.0f, -0.1f }, { 3.0f, 1.25f }, { 0.8f, 0.2f, 0.1f, 1.0f }, 45.0f);
	Envii::Renderer2D::DrawQuadRotate({ 0.0f, 0.0f, 0.0f }, { 3.0f, 1.25f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Tex, -45.0f, 2.0f, 1);

	Envii::Renderer2D::EndScene();
#endif

	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());

	Envii::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 3.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_StairsTex, 1.0f, 3);
	
	Envii::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnImguiRender()
{
	auto stats = Envii::Renderer2D::GetStats();
	ImGui::Begin("Envii Info");
	ImGui::Text("Render Stats:");
	ImGui::Text("  Quad Count: %d", stats.QuadCount);
	ImGui::Text("  Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Envii::Event& event)
{
	m_CamCtl.OnEvent(event);

	Envii::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Envii::KeyPressEvent>(EV_BIND_EVENT_CB(Sandbox2DLayer::OnKeyPressEvent));
}

bool Sandbox2DLayer::OnKeyPressEvent(Envii::KeyPressEvent& event)
{
	return false;
}

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "Sandbox2DLayer.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Envii::Layer("Sandbox2DLayer"), 
	  m_CamCtl(1.778f),
	  m_Tex(Envii::Texture2D::Create("assets/textures/Kreator.png", 1))
	  //m_SquareTex(Envii::Texture2D::Create("assets/textures/Checkerboard.png", 1)
{
	
}

void Sandbox2DLayer::OnAttach()
{
	
}

void Sandbox2DLayer::OnDetach()
{
	Envii::Renderer2D::Shutdown();
}

void Sandbox2DLayer::OnUpdate(Envii::TimeStep ts)
{
	PROFILE_SCOPE("SandboxLayer::OnUpdate()", m_ProfileResults);

	m_CamCtl.OnUpdate(ts);
	
	Envii::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1.0f });
	Envii::RenderCommand::Clear();

	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());
	
	Envii::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 5.6f, 5.6f }, { 0.99f, 0.99f, 0.99f, 1.0f });
	Envii::Renderer2D::DrawQuad({ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.99f, 0.99f, 0.99f, 1.0f }, m_Tex, 1);
	Envii::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.99f, 0.99f, 0.99f, 1.0f }, m_Tex, 1);

	Envii::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnImguiRender()
{
	PROFILE_SCOPE("Sandbox::OnImguiRender()", m_ProfileResults);
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy_s(label, result.Name);
		strcat_s(label, "  %.3f ms");
		ImGui::Text(label, result.Time);
	}

	m_ProfileResults.clear();
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

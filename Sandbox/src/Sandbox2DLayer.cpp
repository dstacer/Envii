#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2DLayer.h"
#include "imgui.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Envii::Layer("Sandbox2DLayer"), 
	  //m_Pos(0.f), 
	  //m_SquarePos(0.f),
	  m_CamCtl(1.778f)
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


	m_CamCtl.OnUpdate(ts);
	
	Envii::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1.0f });
	Envii::RenderCommand::Clear();

	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());
	
	Envii::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f }, 0);
	Envii::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 0.6f, 0.6f }, { 0.5f, 0.5f, 0.5f, 1.0f }, 0);

	Envii::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnImguiRender()
{

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

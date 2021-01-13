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

Sandbox2DLayer::~Sandbox2DLayer()
{
	
}

void Sandbox2DLayer::OnAttach()
{

}

void Sandbox2DLayer::OnDetach()
{
	
}

void Sandbox2DLayer::OnUpdate(Envii::TimeStep ts)
{
	EV_PROFILE_FUNCTION();

	m_CamCtl.OnUpdate(ts);
	
	Envii::RenderCommand::SetClearColor({ 0.4f, 0.4f, 0.4f, 1.0f });
	Envii::RenderCommand::Clear();

	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());
	
	Envii::Renderer2D::DrawQuad({ -2.0f, -2.0f, -0.2f }, { 12.0f, 5.0f }, { 0.1f, 0.2f, 0.8f, 1.0f });
	Envii::Renderer2D::DrawQuad({ 2.0f, -4.0f, 0.0f }, { 6.0f, 2.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Tex, 2.0f, 1);
	//Envii::Renderer2D::DrawQuadRotate({ -2.0f, 4.0f, -0.1f }, { 3.0f, 1.25f }, { 0.25f, 0.2f, 0.8f, 1.0f }, 45.0f);
	//Envii::Renderer2D::DrawQuadRotate({ 2.0f, 4.0f, 0.0f }, { 3.0f, 1.25f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Tex, 0.0f, 1.0f, 1);

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

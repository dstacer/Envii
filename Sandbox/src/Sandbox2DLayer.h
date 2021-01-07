#pragma once

#include "Envii.h"

class Sandbox2DLayer : public Envii::Layer
{
public:
	Sandbox2DLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Envii::TimeStep) override;
	void OnImguiRender() override;
	void OnEvent(Envii::Event& event) override;
	
	bool OnKeyPressEvent(Envii::KeyPressEvent& event);

private:
	Envii::CameraController m_CamCtl;
	Envii::Ref<Envii::Texture2D> m_Tex;
	Envii::Ref<Envii::Texture2D> m_SquareTex;

	std::vector<Envii::ProfileResult> m_ProfileResults;
};
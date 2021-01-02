#pragma once

#include "Envii.h"

class TestLayer : public Envii::Layer
{
public:
	TestLayer();

	void OnUpdate(Envii::TimeStep) override;
	void OnImguiRender() override;
	void OnEvent(Envii::Event& event) override;
	
	bool OnKeyPressEvent(Envii::KeyPressEvent& event);

private:
	Envii::Ref<Envii::VertexArray> m_TriVao;
	Envii::Ref<Envii::VertexArray> m_QuadVao;

	Envii::Ref<Envii::Shader> m_TriShader;
	Envii::Ref<Envii::Shader> m_QuadShader;
	Envii::Ref<Envii::OrthoCamera> m_Camera;

	glm::vec3 m_TriPos, m_QuadPos;
};
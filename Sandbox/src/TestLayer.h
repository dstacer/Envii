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
	std::shared_ptr<Envii::VertexArray> m_TriVao;
	std::shared_ptr<Envii::VertexArray> m_QuadVao;

	std::shared_ptr<Envii::Shader> m_TriShader;
	std::shared_ptr<Envii::Shader> m_QuadShader;
	std::shared_ptr<Envii::OrthoCamera> m_Camera;

	glm::vec3 m_TriPos, m_QuadPos;
};
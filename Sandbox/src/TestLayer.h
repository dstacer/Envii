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
	Envii::Ref<Envii::VertexArray> m_Vao;
	Envii::Ref<Envii::VertexArray> m_SquareVao;

	Envii::ShaderLibrary m_ShaderLib;
	Envii::Ref<Envii::OrthoCamera> m_Camera;
	Envii::Ref<Envii::Texture2D> m_Tex;
	Envii::Ref<Envii::Texture2D> m_SquareTex;

	glm::vec3 m_Pos, m_SquarePos;
};
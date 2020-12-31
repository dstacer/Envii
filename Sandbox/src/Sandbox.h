#pragma once

#include "Envii.h"
#include "imgui.h"

class Sandbox : public Envii::App
{
public:
	Sandbox();
	~Sandbox();
};

class TestLayer : public Envii::Layer
{
public:
	TestLayer()
		: Layer("TestLayer") {}

	void OnUpdate() override
	{
		/*EV_APP_TRACE("TestLayer::Update");
		if (Envii::Input::IsKeyPressed(EV_KEY_TAB))
			EV_APP_TRACE("TAB KEY PRESSED");
		*/
			
	}

	void OnImguiRender() 
	{
		ImGui::Begin("Sandbox Imgui Test");
		ImGui::Text("This shit works!");
		ImGui::End();
		
	}

	void OnEvent(Envii::Event& event) override
	{
		//EV_APP_INFO("{0}", event);
	}
};
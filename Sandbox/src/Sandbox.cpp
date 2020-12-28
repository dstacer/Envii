#include <iostream>

#include "Sandbox.h"

Sandbox::Sandbox()
{
	PushLayer(new TestLayer());
	PushOverlay(new Envii::ImguiLayer());
}

Sandbox::~Sandbox()
{
}

Envii::App* Envii::CreateApp()
{
	return new Sandbox();
}

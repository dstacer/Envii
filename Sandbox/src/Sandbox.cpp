#include <iostream>

#include "Sandbox.h"

Sandbox::Sandbox()
{
	PushLayer(new TestLayer());
}

Sandbox::~Sandbox()
{
}

Envii::App* Envii::CreateApp()
{
	return new Sandbox();
}

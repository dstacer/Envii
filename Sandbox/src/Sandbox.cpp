#include <iostream>

#include "EntryPoint.h"
#include "Sandbox.h"
#include "Sandbox2DLayer.h"


Sandbox::Sandbox()
{
	PushLayer(new Sandbox2DLayer());
}

Sandbox::~Sandbox()
{
}

Envii::App* Envii::CreateApp()
{
	return new Sandbox();
}

#include <iostream>

#include "EntryPoint.h"
#include "Sandbox.h"
#include "TestLayer.h"


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

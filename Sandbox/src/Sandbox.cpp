#include <iostream>

#include "Sandbox.h"

Sandbox::Sandbox()
{
}

Sandbox::~Sandbox()
{
}

Envii::App* Envii::CreateApp()
{
	return new Sandbox();
}

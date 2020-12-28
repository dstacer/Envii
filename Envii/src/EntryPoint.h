#pragma once

#ifdef EV_PLATFORM_WINDOWS

extern Envii::App* Envii::CreateApp();

int main(int argc, char** argv)
{
	Envii::Log::Init();
	EV_CORE_INFO("Core logger initialized.");
	EV_APP_INFO("Client logger initialized.");
	Envii::App* app = Envii::CreateApp();
	app->Run();
	delete app;
}
#endif
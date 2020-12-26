#pragma once

#ifdef EV_PLATFORM_WINDOWS

extern Envii::App* Envii::CreateApp();

int main(int argc, char** argv)
{
	Envii::Log::Init();
	EV_CORE_WARN("Core logger initialized.");
	int a = 27;
	EV_APP_TRACE("Client logger initialized. Test={0}", a);
	Envii::App* app = Envii::CreateApp();
	app->Run();
	delete app;
}
#endif
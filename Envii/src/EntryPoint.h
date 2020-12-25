#pragma once

#ifdef EV_PLATFORM_WINDOWS

extern Envii::App* Envii::CreateApp();

int main(int argc, char** argv)
{
	Envii::App* app = Envii::CreateApp();
	app->Run();
	delete app;
}
#endif
#pragma once
//#include <memory>
#include "Core.h"
#include "Window.h"

namespace Envii
{
	class App
	{
	public:	
		App();
		virtual ~App();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// Client must define this function to create their own Envii::App
	App* CreateApp();
}


#pragma once
#include "Core.h"

namespace Envii
{
	class App
	{
	public:	
		App();
		virtual ~App();

		void Run();
	};

	// Client must define this function to create their own Envii::App
	App* CreateApp();
}


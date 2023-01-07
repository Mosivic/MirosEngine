#pragma once
#include "Core.h"


namespace Miros {
	class MIROS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}



#include "Application.h"
#include "Events/AppicationEvent.h"
#include "Log.h"

namespace Miros {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		MRS_CORE_TRACE(e.ToString());

		while (true)
		{

		}
	}
}

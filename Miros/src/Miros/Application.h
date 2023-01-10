#pragma once
#include "Core.h"
#include "Window.h"
#include <memory>
#include "Events/AppicationEvent.h"
#include "Events/Event.h"

namespace Miros {
	class MIROS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}



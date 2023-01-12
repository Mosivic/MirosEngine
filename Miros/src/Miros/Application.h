#pragma once
#include "Core.h"
#include "Window.h"
#include <memory>
#include "Events/AppicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"

namespace Miros {
	class MIROS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}



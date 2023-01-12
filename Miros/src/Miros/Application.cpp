#include "Application.h"
#include <GLFW/glfw3.h>
#include "Log.h"

namespace Miros {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		//����Window
		m_Window = std::unique_ptr<Window>(Window::Create());
		//��Window�����¼��ص�����,��������Ϊevent
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) {
		EventDispather dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		MRS_CORE_INFO(" {0} ", e.ToString());

		//��β��ͷ���ݸ�Layer,��ĳһLayer����ΪHandled,��������
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	//wrap LayerStack
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	//warp LayerStack
	void Application::PushOverlayer(Layer* layer)
	{
		m_LayerStack.PushOverlayer(layer);
	}


	void Application::Run()
	{
		while (m_Running)
		{
			//����Layers
			for (auto layer: m_LayerStack)
			{
				layer->OnUpdate();
			}
			//����Window
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}

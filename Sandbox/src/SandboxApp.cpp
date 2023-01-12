#include <Miros.h>

//×Ô¶¨ÒåLayer
class ExampleLayer : public Miros::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{}

	void OnUpdate() override
	{
		MRS_INFO("example OnUpdate");
	}

	void OnEvent(Miros::Event& event) override
	{
		MRS_TRACE("{0}", event.ToString());
	}
};


class Sandbox : public Miros::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	};
	~Sandbox() {};
};


Miros::Application* Miros::CreateApplication() {
	return new Sandbox();
}
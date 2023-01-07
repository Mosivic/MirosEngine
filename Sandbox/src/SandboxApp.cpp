#include <Miros.h>


class Sandbox : public Miros::Application {
public:
	Sandbox() {};
	~Sandbox() {};
};



Miros::Application* Miros::CreateApplication() {
	return new Sandbox();
}
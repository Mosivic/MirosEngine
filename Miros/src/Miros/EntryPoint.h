#pragma once


#ifdef  MRS_PLATFORM_WINDOWS

extern Miros::Application* Miros::CreateApplication();

int main(int argc, char** argv) {

	Miros::Log::Init();
	MRS_CORE_WARN("Initialized Log!");
	MRS_CORE_INFO("Hello");

	auto app = Miros::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif //  MRS_PLATFORM_WINDOWS

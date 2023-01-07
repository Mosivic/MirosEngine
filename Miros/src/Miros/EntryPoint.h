#pragma once


#ifdef  MRS_PLATFORM_WINDOWS

extern Miros::Application* Miros::CreateApplication();

int main(int argc, char** argv) {
	printf("Miro Engine.\n");
	auto app = Miros::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif //  MRS_PLATFORM_WINDOWS

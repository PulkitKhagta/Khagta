#pragma once


#ifdef KG_PLATFORM_WINDOWS

extern Khagta::Application* Khagta::CreateApplication();

int main(int argc, char** argv)
{
	printf("Khagta Engine");
	auto app = Khagta::CreateApplication();
	app->Run();
	delete app;
}

#endif // KG_PLATFORM_WINDOWS

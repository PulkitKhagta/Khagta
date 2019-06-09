#pragma once


#ifdef KG_PLATFORM_WINDOWS

extern Khagta::Application* Khagta::CreateApplication();

int main(int argc, char** argv)
{
	Khagta::Log::Init();
	KG_CORE_WARN("Initialized Log!");
	int a = 5;
	KG_INFO("Hello! Var ={0}",a);

	auto app = Khagta::CreateApplication();
	app->Run();
	delete app;
}

#endif // KG_PLATFORM_WINDOWS

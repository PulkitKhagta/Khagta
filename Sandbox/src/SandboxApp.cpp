#include <Khagta.h>

class Sandbox : public Khagta::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Khagta::Application* Khagta::CreateApplication()
{
	return new Sandbox();
}
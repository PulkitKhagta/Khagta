#include <Khagta.h>

class ExampleLayer : public Khagta::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		KG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Khagta::Event& event) override
	{
		KG_TRACE("{0}", event);
	}

};

class Sandbox : public Khagta::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Khagta::Application* Khagta::CreateApplication()
{
	return new Sandbox();
}


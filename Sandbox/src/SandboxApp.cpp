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
		//KG_INFO("ExampleLayer::Update");

		if (Khagta::Input::IsKeyPressed(KG_KEY_TAB))
			KG_TRACE("The key is pressed (poll)!");
	}

	void OnEvent(Khagta::Event& event) override
	{
		//KG_TRACE("{0}", event);
		if (event.GetEventType() == Khagta::EventType::KeyPressed)
		{
			Khagta::KeyPressedEvent& e = (Khagta::KeyPressedEvent&)event;
			if(e.GetKeyCode() == KG_KEY_TAB)
				KG_TRACE("The key is pressed (event)!");
			KG_TRACE("{0}", (char)e.GetKeyCode());
		}
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


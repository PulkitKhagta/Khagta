#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Khagta/LayerStack.h"
#include "Khagta/Events/ApplicationEvent.h"
#include "Window.h"

namespace Khagta
{
	class KHAGTA_API Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

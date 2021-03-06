#pragma once

#include "Core.h"
#include "Khagta/Events/Event.h"
#include "Khagta/Core/LayerStack.h"
#include "Khagta/Events/ApplicationEvent.h"
#include "Window.h"

#include "Khagta/Core/Timestep.h"

#include "Khagta/imGui/imGuiLayer.h"

namespace Khagta
{
	class   Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		imGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

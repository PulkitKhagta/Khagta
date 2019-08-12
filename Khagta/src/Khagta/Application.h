#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Khagta/LayerStack.h"
#include "Khagta/Events/ApplicationEvent.h"
#include "Window.h"

#include "Khagta/Renderer/Shader.h"
#include "Khagta/Renderer/Buffer.h"
#include "Khagta/Renderer/VertexArray.h"

#include "imGui/imGuiLayer.h"

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

		std::unique_ptr<Window> m_Window;
		imGuiLayer* m_imGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_PurpleShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

#pragma once

#include "Khagta/Layer.h"

#include "Khagta/Events/ApplicationEvent.h"
#include "Khagta/Events/KeyEvent.h"
#include "Khagta/Events/MouseEvent.h"

namespace Khagta {

	class KHAGTA_API imGuiLayer : public Layer
	{
	public:
		imGuiLayer();
		~imGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}
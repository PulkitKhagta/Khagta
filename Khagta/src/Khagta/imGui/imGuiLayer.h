#pragma once

#include "Khagta/Core/Layer.h"

#include "Khagta/Events/ApplicationEvent.h"
#include "Khagta/Events/KeyEvent.h"
#include "Khagta/Events/MouseEvent.h"

namespace Khagta {

	class  imGuiLayer : public Layer
	{
	public:
		imGuiLayer();
		~imGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}
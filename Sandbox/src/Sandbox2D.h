#pragma once

#include "Khagta.h"
class Sandbox2D : public Khagta::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Khagta::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Khagta::Event& e) override;

private:
	Khagta::OrthographicCameraController m_CameraController;

	//Temp
	Khagta::Ref<Khagta::VertexArray> m_SquareVA;
	Khagta::Ref<Khagta::Shader> m_FlatColorShader;

	Khagta::Ref<Khagta::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

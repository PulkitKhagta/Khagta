#include <Khagta.h>
#include <Khagta/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Khagta::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Khagta::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.1f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.8f, 0.2f, 1.0f
		};

		Khagta::Ref<Khagta::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Khagta::VertexBuffer::Create(vertices, sizeof(vertices)));


		Khagta::BufferLayout layout = {
			{Khagta::ShaderDataType::Float3, "a_Position"},
			{Khagta::ShaderDataType::Float4, "a_Color"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Khagta::Ref<Khagta::IndexBuffer> indexBuffer;
		indexBuffer.reset(Khagta::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Khagta::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Khagta::Ref<Khagta::VertexBuffer> squareVB;
		squareVB.reset(Khagta::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{Khagta::ShaderDataType::Float3, "a_Position"},
			{Khagta::ShaderDataType::Float2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Khagta::Ref<Khagta::IndexBuffer> squareIB;
		squareIB.reset(Khagta::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Khagta::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShadervertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Khagta::Shader::Create("FlatColor", flatColorShadervertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		m_Texture = Khagta::Texture2D::Create("Assets/Textures/367.jpg");
		m_PixelHuman = Khagta::Texture2D::Create("Assets/Textures/PixelHuman.png");

		std::dynamic_pointer_cast<Khagta::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Khagta::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Khagta::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		//Render
		Khagta::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Khagta::RenderCommand::Clear();

		//////
		Khagta::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Khagta::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Khagta::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int  x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Khagta::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Khagta::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_PixelHuman->Bind();
		Khagta::Renderer::Submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		//Triangle
		//Khagta::Renderer::Submit(m_Shader, m_VertexArray);

		Khagta::Renderer::EndScene();
		//////
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Khagta::Event& e) override
	{
		m_CameraController.OnEvent(e);
		
	}

private:
	Khagta::ShaderLibrary m_ShaderLibrary;
	Khagta::Ref<Khagta::Shader> m_Shader;
	Khagta::Ref<Khagta::VertexArray> m_VertexArray;

	Khagta::Ref<Khagta::Shader> m_FlatColorShader;
	Khagta::Ref<Khagta::VertexArray> m_SquareVA;

	Khagta::Ref<Khagta::Texture2D> m_Texture, m_PixelHuman;

	Khagta::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Khagta::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
		
	}
};

Khagta::Application* Khagta::CreateApplication()
{
	return new Sandbox();
}


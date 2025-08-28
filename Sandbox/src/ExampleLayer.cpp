#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>

ExampleLayer::ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
{
	m_VertexArray = Mizu::VertexArray::Create();

	float vertices[4 * 5] = {
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, //1.0f, 0.5f, 0.2f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //0.5f, 0.7f, 0.5f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //0.2f, 0.3f, 0.5f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, //1.0f, 0.2f, 0.7f,
	};

	Mizu::Ref<Mizu::VertexBuffer> vertexBuffer;
	vertexBuffer = Mizu::VertexBuffer::Create(vertices, sizeof(vertices));
	Mizu::BufferLayout layout = {
		{ Mizu::ShaderDataType::Float3, "a_Position" },
		{ Mizu::ShaderDataType::Float2, "a_TexCoord" },
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3 * 2] = {
		3, 1, 0,
		3, 2, 1,
	};
	Mizu::Ref<Mizu::IndexBuffer> indexBuffer;
	indexBuffer = Mizu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = Mizu::Shader::Create(/*"GradientOverlay",*/ "assets/shaders/Shader.glsl");

	m_Shader->Bind();
	m_Shader->SetFloat3("u_TL", { 1.0f, 0.2f, 0.7f });
	m_Shader->SetFloat3("u_TR", { 1.0f, 0.5f, 0.2f });
	m_Shader->SetFloat3("u_BL", { 0.2f, 0.3f, 0.5f });
	m_Shader->SetFloat3("u_BR", { 0.5f, 0.7f, 0.5f });

	m_Texture = Mizu::Texture2D::Create("assets/textures/luxurious_koi_alpha.png");

	m_Shader->Bind();
	m_Shader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{

}

void ExampleLayer::OnDetach()
{

}

void ExampleLayer::OnUpdate(Mizu::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Mizu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 }); // 0.2f, 0.3f, 0.3f, 1.0f
	Mizu::RenderCommand::Clear();

	Mizu::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Texture->Bind();
	Mizu::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));

	Mizu::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{

}

void ExampleLayer::OnEvent(Mizu::Event& event)
{
	m_CameraController.OnEvent(event);
}
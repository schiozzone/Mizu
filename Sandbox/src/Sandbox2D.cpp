#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	MZ_PROFILE_FUNCTION();
	m_Texture = Mizu::Texture2D::Create("assets/textures/uv.png");
}

void Sandbox2D::OnDetach()
{
	MZ_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Mizu::Timestep ts)
{
	MZ_PROFILE_FUNCTION();
	m_CameraController.OnUpdate(ts);

	Mizu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 }); // 0.2f, 0.3f, 0.3f, 1.0f
	Mizu::RenderCommand::Clear();

	Mizu::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Mizu::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 1.0f, 1.0f }, m_Color);
	Mizu::Renderer2D::DrawQuad({ 0.5f, 0.0f }, { 1.0f, 1.0f }, m_Texture);

	Mizu::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	MZ_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::Text("Quad Colour:");
	ImGui::ColorEdit4("Quad Colour", glm::value_ptr(m_Color),
		ImGuiColorEditFlags_NoInputs |
		ImGuiColorEditFlags_NoLabel |
		ImGuiColorEditFlags_AlphaBar |
		ImGuiColorEditFlags_NoSidePreview |
		ImGuiColorEditFlags_PickerHueWheel);
	ImGui::End();
}

void Sandbox2D::OnEvent(Mizu::Event& event)
{
	m_CameraController.OnEvent(event);
}
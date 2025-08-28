#pragma once

#include "Mizu.h"

class Sandbox2D : public Mizu::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Mizu::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Mizu::Event& event) override;
private:
	Mizu::OrthographicCameraController m_CameraController;

	Mizu::Ref<Mizu::Texture2D> m_Texture;
	glm::vec4 m_Color = { 0.87f, 0.28f, 0.35f, 1.0f }; // { 0.2f, 0.4f, 0.6f, 1.0f };
};


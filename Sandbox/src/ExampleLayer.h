#pragma once

#include "Mizu.h"

class ExampleLayer : public Mizu::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Mizu::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Mizu::Event& e) override;
private:
	Mizu::Ref<Mizu::Shader> m_Shader;
	Mizu::Ref<Mizu::VertexArray> m_VertexArray;
	Mizu::Ref<Mizu::Texture2D> m_Texture;

	Mizu::OrthographicCameraController m_CameraController;
};
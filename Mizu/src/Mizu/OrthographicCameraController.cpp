#include "mzpch.h"
#include "Mizu/OrthographicCameraController.h"

#include "Mizu/Core/Input.h"
#include "Mizu/Core/KeyCodes.h"

namespace Mizu {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		MZ_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(MZ_KEY_A))
		{
			m_CameraPosition.x -= m_CameraRotationCos * m_CameraTranslationSpeed * m_ZoomLevel * ts;
			m_CameraPosition.y -= m_CameraRotationSin * m_CameraTranslationSpeed * m_ZoomLevel * ts;
		}
		if (Input::IsKeyPressed(MZ_KEY_D))
		{
			m_CameraPosition.x += m_CameraRotationCos * m_CameraTranslationSpeed * m_ZoomLevel * ts;
			m_CameraPosition.y += m_CameraRotationSin * m_CameraTranslationSpeed * m_ZoomLevel * ts;
		}
		if (Input::IsKeyPressed(MZ_KEY_S))
		{
			m_CameraPosition.x += m_CameraRotationSin * m_CameraTranslationSpeed * m_ZoomLevel * ts;
			m_CameraPosition.y -= m_CameraRotationCos * m_CameraTranslationSpeed * m_ZoomLevel * ts;
		}
		if (Input::IsKeyPressed(MZ_KEY_W))
		{
			m_CameraPosition.x -= m_CameraRotationSin * m_CameraTranslationSpeed * m_ZoomLevel * ts;
			m_CameraPosition.y += m_CameraRotationCos * m_CameraTranslationSpeed * m_ZoomLevel * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(MZ_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
				PrecalculateTrigFunc();
			}
			if (Input::IsKeyPressed(MZ_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
				PrecalculateTrigFunc();
			}

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation); // OrthographicCamera::RecalculateViewMatrix() gets called twice
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(MZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	void OrthographicCameraController::PrecalculateTrigFunc()
	{
		m_CameraRotationCos = cos(glm::radians(m_CameraRotation));
		m_CameraRotationSin = sin(glm::radians(m_CameraRotation));
	}
}

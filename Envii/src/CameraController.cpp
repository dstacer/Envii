#include "evpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"
#include "KeyCodes.h"
#include "CameraController.h"

namespace Envii
{
	CameraController::CameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio),
		  m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	CameraController::~CameraController()
	{
	}

	void CameraController::OnUpdate(TimeStep ts)
	{
		// User Camera Translation
		if (Envii::Input::IsKeyPressed(EV_KEY_LEFT))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-6.f * ts, 0.f, 0.f));
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_RIGHT))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(6.f * ts, 0.f, 0.f));
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_UP))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.f, 6.f * ts, 0.f));
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_DOWN))
		{
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0.f, -6.f * ts, 0.f));
		}

		// User Camera Rotation
		if (Envii::Input::IsKeyPressed(EV_KEY_D))
		{
			m_Camera.SetRotation(m_Camera.GetRotation() - 360.f * ts);
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_F))
		{
			m_Camera.SetRotation(m_Camera.GetRotation() + 360.f * ts);
		}
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(EV_BIND_EVENT_CB(CameraController::OnMouseScroll));
		dispatcher.Dispatch<WindowResizeEvent>(EV_BIND_EVENT_CB(CameraController::OnWindowResize));
	}

	const OrthoCamera& CameraController::GetCamera() const
	{
		return m_Camera;
	}

	bool CameraController::OnMouseScroll(MouseScrollEvent e)
	{
		m_ZoomLevel += e.GetAmountY() * -0.1f;
		m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
		return false;
	}

	bool CameraController::OnWindowResize(WindowResizeEvent e)
	{
		m_AspectRatio = (float)e.GetWidth() / e.GetHeight();
		m_Camera.SetProjection(m_AspectRatio, m_ZoomLevel);
		return false;
	}
}
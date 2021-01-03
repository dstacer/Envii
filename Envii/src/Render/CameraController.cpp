#include "evpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "CameraController.h"

namespace Envii
{
	CameraController::CameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio),
		  m_Camera(-aspectRatio * m_VerticalExtent, aspectRatio * m_VerticalExtent, -m_VerticalExtent, m_VerticalExtent)
	{
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::OnUpdate(TimeStep ts)
	{
		// User Camera Translation
		if (Envii::Input::IsKeyPressed(EV_KEY_A))
		{
			m_Position.x -= cos(glm::radians(m_Rotation)) * m_TransSpeed * ts;
			m_Position.y -= sin(glm::radians(m_Rotation)) * m_TransSpeed * ts;
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_D))
		{
			m_Position.x += cos(glm::radians(m_Rotation)) * m_TransSpeed * ts;
			m_Position.y += sin(glm::radians(m_Rotation)) * m_TransSpeed * ts;
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_W))
		{
			m_Position.x -= sin(glm::radians(m_Rotation)) * m_TransSpeed * ts;
			m_Position.y += cos(glm::radians(m_Rotation)) * m_TransSpeed * ts; 
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_S))
		{
			m_Position.x += sin(glm::radians(m_Rotation)) * m_TransSpeed * ts;
			m_Position.y -= cos(glm::radians(m_Rotation)) * m_TransSpeed * ts;
		}

		// User Camera Rotation - Positive rotation is CCW (math convention)
		if (Envii::Input::IsKeyPressed(EV_KEY_Q))
		{
			m_Rotation += m_RotSpeed * ts;
		}
		else if (Envii::Input::IsKeyPressed(EV_KEY_E))
		{
			m_Rotation -= m_RotSpeed * ts;
		}

		m_Camera.SetRotation(m_Rotation);
		m_Camera.SetPosition(m_Position);

		// Adjust cam translation speed to a account for zoom
		m_TransSpeed = 1.5f * m_VerticalExtent;
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
		m_VerticalExtent -= e.GetAmountY() * 0.1f;
		m_VerticalExtent = std::max(m_VerticalExtent, 0.1f);
		m_Camera.SetProjection(m_AspectRatio, m_VerticalExtent);
		return false;
	}

	bool CameraController::OnWindowResize(WindowResizeEvent e)
	{
		m_AspectRatio = (float)e.GetWidth() / e.GetHeight();
		m_Camera.SetProjection(m_AspectRatio, m_VerticalExtent);
		return false;
	}
}
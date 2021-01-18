#pragma once
#include <glm/glm.hpp>
#include "../Core/Timestep.h"
#include "../Events/AppEvent.h"
#include "../Events/MouseEvent.h"
#include "OrthoCamera.h"

namespace Envii
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio);
		virtual ~CameraController();

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		const OrthoCamera& GetCamera() const;
		void SetVerticalExtent(float screenHalfHeight) { 
			m_VerticalExtent = screenHalfHeight; 
			m_Camera.SetProjection(m_AspectRatio, screenHalfHeight);
		}
		void SetAspectRatio(uint32_t width, uint32_t height) {
			m_AspectRatio = (float)width / height;
			m_Camera.SetProjection(m_AspectRatio, m_VerticalExtent);
		}

	private:
		bool OnMouseScroll(MouseScrollEvent e);
		bool OnWindowResize(WindowResizeEvent e);

	private:
		float m_AspectRatio;
		float m_VerticalExtent = 1.0f;
		OrthoCamera m_Camera;
		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;
		float m_RotSpeed = 270.f;
		float m_TransSpeed = 6.0f;
	};
}
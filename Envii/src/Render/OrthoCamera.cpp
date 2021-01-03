#include "evpch.h"

#include <glm/gtc/matrix_transform.hpp>
#include "OrthoCamera.h"

namespace Envii
{
	OrthoCamera::OrthoCamera(const glm::mat4& projMat, const glm::vec3& pos)
		: m_Position(pos),
		  m_Rotation(0.0f),
		  m_ProjMat(projMat),
		  m_ViewMat(1.0)
	{
		UpdateView();
	}

	OrthoCamera::OrthoCamera(float left, float right, float top, float bottom)
		: m_Position(0.0f),
		  m_Rotation(0.0f),
		  m_ProjMat(glm::ortho(left, right, top, bottom)),
		  m_ViewMat(1.0)
	{
		UpdateView();
	}

	void OrthoCamera::SetProjection(float aspectRatio, float zoomLevel)
	{
		m_ProjMat = glm::ortho(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		m_ViewProjMat = m_ProjMat * m_ViewMat;
	}

	void OrthoCamera::UpdateView()
	{
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), m_Rotation, { 0.0f, 0.0f, 1.0f });
		m_ViewMat = glm::inverse(trans * rot);
		m_ViewProjMat = m_ProjMat * m_ViewMat;
	}
}

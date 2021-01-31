#include "evpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "SceneCamera.h"

namespace Envii
{
	void SceneCamera::SetOrthographic(float vertExtent, float orthoNear, float orthoFar)
	{
		m_VertExtent = vertExtent;
		m_OrthoNear = orthoNear;
		m_OrthoFar = orthoFar;
		UpdateProjection();
	}

	void SceneCamera::SetPerspective(float vertFov, float persNear, float persFar)
	{
		m_VertFov = vertFov;
		m_PerspectiveNear = persNear;
		m_PerspectiveFar = persFar;
		UpdateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_Aspect = (float)width / height;
		UpdateProjection();
	}

	void SceneCamera::UpdateProjection()
	{
		if (m_ProjType == ProjectionType::Orthographic)
		{
			float halfHeight = m_VertExtent * 0.5f;
			float halfWidth = m_Aspect * halfHeight;
			m_Projection = glm::ortho(-halfWidth, halfWidth,
									  -halfHeight, halfHeight,
									   m_OrthoNear, m_OrthoFar);
		}
		else
		{
			m_Projection = glm::perspective(glm::radians(m_VertFov), 
											m_Aspect, 
											m_PerspectiveNear, 
											m_PerspectiveFar);
		}
	}
}
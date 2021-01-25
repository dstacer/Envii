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

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_Aspect = (float)width / height;
		UpdateProjection();
	}

	void SceneCamera::UpdateProjection()
	{
		float halfHeight = m_VertExtent * 0.5f;
		float halfWidth = m_Aspect * halfHeight;
		m_Projection = glm::ortho(-halfWidth, halfWidth,
								  -halfHeight, halfHeight,
								   m_OrthoNear, m_OrthoFar);
	}
}
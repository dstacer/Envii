#pragma once

#include "Camera.h"

namespace Envii
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera() = default;
		virtual ~SceneCamera() = default;

		void SetOrthographic(float vertExtent, float orthoNear, float orthoFar);
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetHeight() const { return m_VertExtent; }
		void SetHeight(float vertExtent) { m_VertExtent = vertExtent; UpdateProjection(); }

	private:
		void UpdateProjection();

	private:
		float m_VertExtent = 2.f;
		float m_Aspect = 1.f;
		float m_OrthoNear = -1.f;
		float m_OrthoFar = 1.f;
	};
}
#pragma once

#include "Camera.h"

namespace Envii
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Orthographic = 0, Perspective = 1, NumTypes = 2 };
	public:
		SceneCamera() = default;
		virtual ~SceneCamera() = default;

		void SetOrthographic(float vertExtent, float orthoNear, float orthoFar);
		void SetPerspective(float vertFov, float persNear, float persFar);
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetHeight() const { return m_VertExtent; }
		void SetHeight(float vertExtent) { m_VertExtent = vertExtent; UpdateProjection(); }

		float GetVertFov() const { return m_VertFov; }
		void SetVertFov(float vertFov) { m_VertFov = vertFov; UpdateProjection(); }

		float GeAspectRatio() const { return m_Aspect; }
		void SetAspectRatio(float aspectRatio) { m_Aspect = aspectRatio; UpdateProjection(); }

		ProjectionType GetProjectionType() const { return m_ProjType; }
		void SetProjectionType(ProjectionType type) { m_ProjType = type; UpdateProjection(); }

		float GetOrthoNear() const { return m_OrthoNear; }
		void SetOrthoNear( float nearf) { m_OrthoNear = nearf; UpdateProjection(); }

		float GetOrthoFar() const { return m_OrthoFar; }
		void SetOrthoFar(float farf) { m_OrthoFar = farf; UpdateProjection(); }

		float GetPerspectiveNear() const { return m_PerspectiveNear; }
		void SetPerspectiveNear(float nearf) { m_PerspectiveNear = nearf; UpdateProjection(); }

		float GetPerspectiveFar() const { return m_PerspectiveFar; }
		void SetPerspectiveFar(float farf) { m_PerspectiveFar = farf; UpdateProjection(); }

	private:
		void UpdateProjection();

	private:
		float m_VertExtent = 2.f;
		float m_Aspect = 1.f;
		float m_OrthoNear = -1.f;
		float m_OrthoFar = 1.f;
		float m_VertFov = 30.f;
		float m_PerspectiveNear = 0.f;
		float m_PerspectiveFar = 1000.f;
		ProjectionType m_ProjType = ProjectionType::Orthographic;
	};
}
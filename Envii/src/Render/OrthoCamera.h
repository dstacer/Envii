#pragma once

#include <glm/glm.hpp>

namespace Envii
{
	class OrthoCamera
	{
	public:
		OrthoCamera(const glm::mat4& projMat, const glm::vec3& pos);
		OrthoCamera(float left, float right, float top, float bottom);

		void SetProjection(float aspectRatio, float verticalExtent);
		inline void SetProjection(const glm::mat4 projMat) { m_ProjMat = projMat; }
		inline void SetView(const glm::mat4& viewMat) { m_ViewMat = viewMat; }
		
		inline glm::vec3 GetPosition() { return m_Position; }
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; UpdateView(); }

		inline float GetRotation() { return glm::degrees(m_Rotation); }
		inline void SetRotation(float rotDegs) { m_Rotation = glm::radians(rotDegs); UpdateView(); }

		const inline glm::mat4& GetView() const { return m_ViewMat; }
		const inline glm::mat4& GetProjection() const { return m_ProjMat; }
		const inline glm::mat4& GetViewProjection() const { return m_ViewProjMat; }

	private:
		void UpdateView();

	private:
		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;
		glm::mat4 m_ViewProjMat;
		glm::vec3 m_Position;
		float m_Rotation;
	};
}
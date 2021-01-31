#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Scene/Component.h"
#include "SceneGraphPanel.h"

namespace Envii
{
	SceneGraphPanel::SceneGraphPanel(const Ref<Scene>& scene)
		: m_Scene(scene) {}

	void SceneGraphPanel::SetScene(const Ref<Scene>& scene)
	{
		m_Scene = scene;
	}

	void SceneGraphPanel::OnImguiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Scene->m_Registry.each([&](auto entityId) 
		{
			Entity e = { entityId, m_Scene.get() };
			DrawEntityNode(e);
		});

		// De-select if user clicks on blank space in panel
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_Selected = {};

		ImGui::End();

		

		ImGui::Begin("Properties");
		if (m_Selected)
			DrawComponents(m_Selected);
		ImGui::End();
	}

	void SceneGraphPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = (m_Selected == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
			m_Selected = entity;

		if (opened)
			ImGui::TreePop();
	}

	void SceneGraphPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag; 
			char buffer[128];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Name", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(entity).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{ 
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Translation", glm::value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}

			/*if (ImGui::DragFloat3("Rotation", glm::value_ptr(transform[3])))
			{
				// Take rotation components and do whatever's needed
			}*/
		}

		if (entity.HasComponent<CameraComponent>())
		{
			auto& camera = entity.GetComponent<CameraComponent>().Cam;
			if (ImGui::TreeNodeEx((void*)typeid(entity).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera - Aspect: %f", camera.GeAspectRatio()))
			{
				const char* projTypes[] = { "Orthographic", "Perspective" };
				ImGui::Checkbox("Primary Camera", &entity.GetComponent<CameraComponent>().Primary);

				if (ImGui::BeginCombo("Projection", projTypes[(int)camera.GetProjectionType()]))
				{
					for (int i = 0; i < 2; i++)
					{
						if (ImGui::Selectable(projTypes[i]))
						{
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}	
					}
					ImGui::EndCombo();
				}

				switch (camera.GetProjectionType())
				{
					case SceneCamera::ProjectionType::Orthographic:
					{
						float height = camera.GetHeight();
						if (ImGui::DragFloat("Height", &height))
							camera.SetHeight(height);
						float nearf = camera.GetOrthoNear();
						if (ImGui::DragFloat("Near", &nearf))
							camera.SetOrthoNear(nearf);
						float farf = camera.GetOrthoFar();
						if (ImGui::DragFloat("Far", &farf))
							camera.SetOrthoFar(farf);

						ImGui::Checkbox("Fixed Aspect", &entity.GetComponent<CameraComponent>().FixedAspect);
						break;
					}
					case SceneCamera::ProjectionType::Perspective:
					{
						float vertfov = camera.GetVertFov();
						if (ImGui::DragFloat("Vert FOV", &vertfov))
							camera.SetVertFov(vertfov);
						float nearf = camera.GetPerspectiveNear();
						if (ImGui::DragFloat("Near", &nearf))
							camera.SetPerspectiveNear(nearf);
						float farf = camera.GetPerspectiveFar();
						if (ImGui::DragFloat("Far", &farf))
							camera.SetPerspectiveFar(farf);
						break;
					}
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{

		}
	}
}

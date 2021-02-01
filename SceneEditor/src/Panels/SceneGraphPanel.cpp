#include <imgui.h>
#include <imgui_internal.h>
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

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.f, float columnWidth = 100.f)
	{
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);

		// Draw label
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());

		// Draw Vec3 controls to the right
		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.f, 0.f });

		// Calc dimensions
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
		ImVec2 buttonSize = { lineHeight + 3.f, lineHeight };

		// Draw Buttons & text fields
		ImGui::PushStyleColor(ImGuiCol_Button, { .8f, .1f, .15f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.f, .2f, .2f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .7f, .05f, .1f, 1.f });
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, .1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { .1f, .8f, .15f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .2f, 1.f, .2f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .05f, .7f, .1f, 1.f });
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, .1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { .05f, .1f, .8f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .1f, .2f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .05f, .05f, .7f, 1.f });
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, .1f);
		ImGui::PopItemWidth();
		
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
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
				auto& trans = entity.GetComponent<TransformComponent>();
				DrawVec3Control("Translation", trans.Translation);
				glm::vec3 rot = glm::degrees(trans.Rotation);
				DrawVec3Control("Rotation", rot);
				trans.Rotation = glm::radians(rot);
				DrawVec3Control("Scale", trans.Scale, 1.f);
				ImGui::TreePop();
			}
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
			if (ImGui::TreeNodeEx((void*)typeid(entity).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
			{
				auto& color = entity.GetComponent<SpriteRendererComponent>().Color;
				ImGui::ColorEdit4("Color", glm::value_ptr(color));
				ImGui::TreePop();
			}
		}
	}
}

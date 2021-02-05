#include <imgui.h>
#include <imgui_internal.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Scene/Component.h"
#include "Envii.h"
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

		// Right click on blank space (outside any item)
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("New Entity"))
				m_Scene->CreateEntity();

			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_Selected)
		{
			DrawComponents(m_Selected);
		}
		ImGui::End();
	}

	void SceneGraphPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = (m_Selected == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
			m_Selected = entity;

		// Right click on item to delete
		bool deleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			// Mark for delete if needed.  Defer delete until children
			// are rendered
			if (ImGui::MenuItem("Delete"))
				deleted = true; 

			ImGui::EndPopup();
		}

		// Render children
		if (opened)
			ImGui::TreePop();

		// Handle Deletion
		if (deleted)
		{
			if (m_Selected == entity)
				m_Selected = {};

			m_Scene->DestroyEntity(entity);
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.f, float columnWidth = 100.f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[Fonts::OpenSansBold];

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
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, .1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { .1f, .8f, .15f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .2f, 1.f, .2f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .05f, .7f, .1f, 1.f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, .1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { .05f, .1f, .8f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { .1f, .2f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { .05f, .05f, .7f, 1.f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, .1f);
		ImGui::PopItemWidth();
		
		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	template <typename T, typename UIFunction>
	static void DrawComponent(const std::string& label, Entity entity, bool removable, UIFunction customFunc)
	{
		if (entity.HasComponent<T>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4.f, 4.f });
			ImVec2 contentWidth = ImGui::GetContentRegionAvail();
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen		| ImGuiTreeNodeFlags_Framed		  | 
													 ImGuiTreeNodeFlags_SpanAvailWidth  | ImGuiTreeNodeFlags_FramePadding | 
													 ImGuiTreeNodeFlags_AllowItemOverlap;

			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)((uint32_t)entity + typeid(T).hash_code()), treeNodeFlags, label.c_str());
			ImGui::PopStyleVar();
			bool remove = false;
			if (removable)
			{
				// Add button to open component context menu
				ImGui::SameLine(contentWidth.x - lineHeight * 0.5f);
				if (ImGui::Button("...", { lineHeight, lineHeight }))
				{
					ImGui::OpenPopup(label.c_str());
				}
				

				// Add Remove item to context menu
				if (ImGui::BeginPopup(label.c_str()))
				{
					if (ImGui::MenuItem("Remove Component"))
						remove = true;

					ImGui::EndPopup();
				}
			}

			if (open)
			{
				auto& component = entity.GetComponent<T>();
				customFunc(component);
				ImGui::TreePop();
			}

			if (remove)
				entity.RemoveComponent<T>();
		}
	}

	void SceneGraphPanel::DrawComponents(Entity entity)
	{
		// Show editable name field
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag; 
			char buffer[128];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1.f);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComp");

		if (ImGui::BeginPopup("AddComp"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_Selected.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_Selected.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		// Show the transform component UI
		DrawComponent<TransformComponent>("Transform", entity, false, [](auto& component)
		{
			DrawVec3Control("Translation", component.Translation);
			glm::vec3 rot = glm::degrees(component.Rotation);
			DrawVec3Control("Rotation", rot);
			component.Rotation = glm::radians(rot);
			DrawVec3Control("Scale", component.Scale, 1.f);
		});

		// Show the camera component UI
		DrawComponent<CameraComponent>("Camera", entity, true, [](auto& component)
		{
			const char* projTypes[] = { "Orthographic", "Perspective" };
			auto& camera = component.Cam;
			ImGui::Checkbox("Primary Camera", &component.Primary);

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

					ImGui::Checkbox("Fixed Aspect", &component.FixedAspect);
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
		});
	
		// Show the sprite renderer component UI
		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, true, [](auto& component) 
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
		});
	}
}

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include "ImGuizmo.h"
#include "EditorLayer.h"

namespace Envii
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), 
		  m_ActiveScene(CreateRef<Scene>()),
		  //m_Rect(m_ActiveScene->CreateEntity("Square")),
		  m_Camera(m_ActiveScene->CreateEntity("Camera"))
	{
		m_Camera.AddComponent<CameraComponent>();
	}

	EditorLayer::~EditorLayer()
	{
	
	}

	void EditorLayer::OnAttach()
	{
		//m_Tex = Texture2D::Create("assets/textures/Kreator.png", 1);
		//m_SquareTex = Texture2D::Create("assets/textures/Checkerboard.png", 2);
		//m_SpriteSheet = Texture2D::Create("assets/textures/RPGpack_sheet.png", 3);
		//m_TreeTex = SubTexture2D::CreateFromIndices(m_SpriteSheet, glm::vec2(2.f, 1.f), 64.f, glm::vec2(1, 2));
	
		FbSpecs fbSpecs = { App::Get().GetWindow().GetWidth(), App::Get().GetWindow().GetHeight() };

		m_Framebuffer = FrameBuffer::Create(fbSpecs);

		//m_Rect.AddComponent<SpriteRendererComponent>(glm::vec4( 0.f,1.f, 0.f, 1.f ));

		class CameraController : public ScriptableEntity
		{
		public:
			void OnUpdate(TimeStep ts) override { 
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.f;

				if (Input::IsKeyPressed(EV_KEY_A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(EV_KEY_D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(EV_KEY_S))
					translation.y -= speed * ts;
				if (Input::IsKeyPressed(EV_KEY_W))
					translation.y += speed * ts;
			}

			void OnMouseScrollEvent(MouseScrollEvent event) override
			{
				// Handle mouse scroll by zooming camera
				if (GetComponent<CameraComponent>().Primary)
				{
					auto& cam = GetComponent<CameraComponent>().Cam;
					switch (cam.GetProjectionType())
					{
						case SceneCamera::ProjectionType::Orthographic:
						{
							float viewHeight = std::max(cam.GetHeight() - event.GetAmountY() * 0.1f, 0.1f);
							cam.SetHeight(viewHeight);
							break;
						}
						case SceneCamera::ProjectionType::Perspective:
						{
							float vertFov = std::max(cam.GetVertFov() - event.GetAmountY(), 0.1f);
							cam.SetVertFov(vertFov);
							break;
						}
					}
				}	
			}
		};

		m_Camera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_ScenePanel.SetScene(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
	
	}

	void EditorLayer::OnUpdate(TimeStep ts)
	{
		EV_PROFILE_FUNCTION();

		if (FbSpecs specs = m_Framebuffer->GetFrameBufferSpecs(); specs.Width != m_ViewportSize.x || specs.Height != m_ViewportSize.y)
		{
			uint32_t newWidth = (uint32_t)m_ViewportSize.x, newHeight = (uint32_t)m_ViewportSize.y;
			m_Framebuffer->Resize(newWidth, newHeight);
			m_ActiveScene->OnViewportResize(newWidth, newHeight);
		}

		Renderer2D::ResetStats();
	
		// Bind and render to offscreen framebuffer
		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		// Update scene
		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImguiRender()
	{
		auto stats = Renderer2D::GetStats();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();
				
				if (ImGui::MenuItem("Exit"))
					App::Get().Close();

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// Set minimum docked window width before drawing SceneGraphPanel
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinWidth = style.WindowMinSize.x;
		style.WindowMinSize.x = 395.f;
		
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		
		// Draw scene graph panel
		m_ScenePanel.OnImguiRender();

		// Restore minimum window width
		style.WindowMinSize.x = minWinWidth;

		ImGui::Begin("Scene");
		ImGui::Separator();
		ImGui::Text("Render Stats:");
		ImGui::Text("  Quad Count: %d", stats.QuadCount);
		ImGui::Text("  Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Separator();
		ImGui::End();
		
		// Render the scene in the Viewport window
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::Begin("Viewport");

		// Determine whether to consume mouse and keyboard events
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		App::Get().GetImguiLayer()->ConsumeEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		if (viewportSize.x > 0.f && viewportSize.y > 0.f && (m_ViewportSize.x != viewportSize.x || m_ViewportSize.y != viewportSize.y))
		{
			m_ViewportSize = { viewportSize.x, viewportSize.y };
		}
		
		uint32_t fbTexId = m_Framebuffer->GetColorAttachmentId();
		ImGui::Image((void*)fbTexId, 
					 ImVec2((float)m_ViewportSize.x, (float)m_ViewportSize.y),
					 ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
		
		// Render transfrom gizmo
		Entity selected = m_ScenePanel.GetSelectedEntity();
		if (selected && m_CurrGizmoOp != -1)
		{
			Entity primaryCamera = m_ActiveScene->GetPrimaryCamera();
			if (primaryCamera)
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

				// Get cam projection & view
				glm::mat4 viewMatrix = glm::inverse(primaryCamera.GetComponent<TransformComponent>().GetTransform());
				const glm::mat4& projMatrix = primaryCamera.GetComponent<CameraComponent>().Cam.GetProjection();
				
				// Get selected entity transform
				auto& tc = selected.GetComponent<TransformComponent>();
				glm::mat4 transform = tc.GetTransform();
				glm::vec3 origRot = tc.Rotation;

				// Set gizmo snap values
				bool snap = Input::IsKeyPressed(EV_KEY_LEFT_CONTROL);
				float snapValue = 0.5f; // Default for translation
				switch (m_CurrGizmoOp)
				{
				case ImGuizmo::OPERATION::TRANSLATE:
					// already set
					break;
				case ImGuizmo::OPERATION::ROTATE:
					snapValue = 5.f;
					break;
				case ImGuizmo::OPERATION::SCALE:
					snapValue = 0.1f;
					break;
				}
				float snapValues[3] = { snapValue, snapValue, snapValue };

				// Render current gizmo and handle user action
				ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix),
					(ImGuizmo::OPERATION)m_CurrGizmoOp, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform),
					nullptr, snap ? snapValues : nullptr);

				if (ImGuizmo::IsUsing())
				{
					// Get gizmo-altered matrix and decompose back into transform component
					glm::vec3 translation(0.f), rotation(0.f), scale(1.f);
					if (DecomposeTransform(transform, translation, rotation, scale))
					{
						tc.Translation = translation;
						glm::vec3 deltaRot = rotation - origRot;
						tc.Rotation += deltaRot;
						tc.Scale = scale;
					}
				}
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_ActiveScene->OnEvent(event);
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressEvent>(EV_BIND_EVENT_CB(EditorLayer::OnKeyPress));
	}

	bool EditorLayer::OnKeyPress(KeyPressEvent& event)
	{
		// Keyboard shortcuts
		if (event.GetRepeatCount() > 0)
			return false;

		bool shiftPressed = Input::IsKeyPressed(EV_KEY_LEFT_SHIFT) || Input::IsKeyPressed(EV_KEY_RIGHT_SHIFT);
		bool controlPressed = Input::IsKeyPressed(EV_KEY_LEFT_CONTROL) || Input::IsKeyPressed(EV_KEY_RIGHT_CONTROL);
		
		switch (event.GetKeyCode())
		{
			case EV_KEY_S:
			{
				if (shiftPressed && controlPressed)
					SaveSceneAs();
				break;
			}
			case EV_KEY_O:
			{
				if (controlPressed)
					OpenScene();
				break;
			}
			case EV_KEY_N:
			{
				if (controlPressed)
					NewScene();
				break;
			}

			// Gizmo type switching
			case EV_KEY_Q:
				m_CurrGizmoOp = -1;
				break;
			case EV_KEY_W:
				m_CurrGizmoOp = ImGuizmo::OPERATION::TRANSLATE;
				break;
			case EV_KEY_E:
				m_CurrGizmoOp = ImGuizmo::OPERATION::ROTATE;
				break;
			case EV_KEY_R:
				m_CurrGizmoOp = ImGuizmo::OPERATION::SCALE;
				break;
		}		

		return true;
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ScenePanel.SetScene(m_ActiveScene);
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Envii Scene (*.envii)\0*.envii\0");

		if (!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ScenePanel.SetScene(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.DeserializeText(filepath);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Envii Scene (*.envii)\0*.envii\0");

		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.SerializeText(filepath);
		}
	}
}
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "EditorLayer.h"

namespace Envii
{
	static const uint32_t s_PondWidth = 20;

	static const char* s_MapTiles = "00000000000000000000"
									"00000000000000000000"
									"00766666666666666500"
									"00899999999999999400"
									"00899999999999999400"
									"00899999999999999400"
									"00899999999999999400"
									"00899999999999999400"
									"00899999999999999400"
									"00122222222222222300"
									"00000000000000000000"
									"00000000000000000000";

	static const glm::vec2 s_PondTileCoords[(int)PondTile::NumTiles] =
	{
		 { 3.f, 10.f},
		 {10.f, 10.f},
		 {11.f, 10.f},
		 {12.f, 10.f},
		 {12.f, 11.f},
		 {12.f, 12.f},
		 {11.f, 12.f},
		 {10.f, 12.f},
		 {10.f, 11.f},
		 {11.f, 11.f},
	};

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), 
		  m_CamCtl(1.778f),
		  m_ActiveScene(CreateRef<Scene>()),
		  m_Rect(m_ActiveScene->CreateEntity("Square")),
		  m_Camera(m_ActiveScene->CreateEntity("Camera"))
	{
		m_MapWidth = s_PondWidth;
		m_MapHeight = (uint32_t)strlen(s_MapTiles) / m_MapWidth;
		m_Camera.AddComponent<CameraComponent>();
	}

	EditorLayer::~EditorLayer()
	{
	
	}

	void EditorLayer::OnAttach()
	{
		m_Tex = Texture2D::Create("assets/textures/Kreator.png", 1);
		m_SquareTex = Texture2D::Create("assets/textures/Checkerboard.png", 2);
		m_SpriteSheet = Texture2D::Create("assets/textures/RPGpack_sheet.png", 3);
		m_TreeTex = SubTexture2D::CreateFromIndices(m_SpriteSheet, glm::vec2(2.f, 1.f), 64.f, glm::vec2(1, 2));
	
		for (int i = 0; i < (int)PondTile::NumTiles; i++)
		{
			m_TexMap[i] = SubTexture2D::CreateFromIndices(m_SpriteSheet, s_PondTileCoords[i], 64.f, glm::vec2(1, 1));
		}
		FbSpecs fbSpecs = { App::Get().GetWindow().GetWidth(), App::Get().GetWindow().GetHeight() };

		m_Framebuffer = FrameBuffer::Create(fbSpecs);
  
		m_CamCtl.SetVerticalExtent(7.2f);

		m_Rect.AddComponent<SpriteRendererComponent>(glm::vec4( 0.f,1.f, 0.f, 1.f ));

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate() { std::cout << "OnCreate" << std::endl; }
			void OnDestroy() {}
			void OnUpdate(TimeStep ts) { 
				auto& transform = GetComponent<TransformComponent>().Transform;
				float speed = 5.f;

				if (Input::IsKeyPressed(EV_KEY_A))
					transform[3].x -= speed * ts;
				if (Input::IsKeyPressed(EV_KEY_D))
					transform[3].x += speed * ts;
				if (Input::IsKeyPressed(EV_KEY_S))
					transform[3].y -= speed * ts;
				if (Input::IsKeyPressed(EV_KEY_W))
					transform[3].y += speed * ts;
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
			m_CamCtl.SetAspectRatio(newWidth, newHeight);
			m_Framebuffer->Resize(newWidth, newHeight);
			m_ActiveScene->OnViewportResize(newWidth, newHeight);
		}

		if (m_ViewportFocused)
			m_CamCtl.OnUpdate(ts);

		Renderer2D::ResetStats();
	
		// Bind and render to offscreen framebuffer
		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		
#if 0
		Renderer2D::BeginScene(m_CamCtl.GetCamera());
	
		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 10.0f, 10.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_SquareTex, 4.0f, 1);
		for (float x = -10.0f; x < 10.0f; x += 0.1f)
		{
			for (float y = -10.0f; y < 10.0f; y += 0.1f)
			{
				glm::vec4 color = { (x + 6.0f) / 12.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
				Renderer2D::DrawQuad({ x, y, -0.15f }, { 0.08, 0.08 }, color);
			}
		}
		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 3.0f, 1.25f }, { 0.1f, 0.2f, 0.8f, 1.0f });
		Renderer2D::DrawQuadRotate({ 0.0f, 0.0f, -0.1f }, { 3.0f, 1.25f }, { 0.8f, 0.2f, 0.1f, 1.0f }, 45.0f);
		Renderer2D::DrawQuadRotate({ 0.0f, 0.0f, 0.0f }, { 3.0f, 1.25f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Tex, -45.0f, 2.0f, 1);

		Renderer2D::EndScene();
#endif
		//Renderer2D::BeginScene(m_CamCtl.GetCamera());
#if 0
		for (int y = 0; y < (int)m_MapHeight; y++)
			for (int x = 0; x < (int)m_MapWidth; x++)
			{
				// Subtract 48 (ASCII code for 0) from the map tile value to get the
				// index into the array of subtextures
				int idx = (int)s_MapTiles[y * m_MapWidth + x] - 48;

				Ref<SubTexture2D> tile;
				if (m_TexMap.find(idx) != m_TexMap.end())
					tile = m_TexMap[idx];
				else
					tile = m_TreeTex;
				// Since we're iterating through the map from the top down, we need to 
				// invert the y position when drawing, from (mapHeight - 1) to 0
				Renderer2D::DrawQuad({ x - (m_MapWidth - 1) * 0.5f, - y + (m_MapHeight - 1) * 0.5f, -0.2f }, { 1.f, 1.f }, 
											{ 1.0f, 1.0f, 1.0f, 1.0f },
											tile, 1.0f, 3);
			}


		Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 1.f, 1.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_TreeTex, 1.0f, 3);
#endif	
		// Update scene
		m_ActiveScene->OnUpdate(ts);
		//Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImguiRender()
	{
		auto stats = Renderer2D::GetStats();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					App::Get().Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		
		// Draw scene graph panel
		m_ScenePanel.OnImguiRender();

		ImGui::Begin("Scene");
		if (m_Rect)
		{
			ImGui::Separator();
			const std::string& tag = m_Rect.GetComponent<TagComponent>().Tag;
			ImGui::Text(tag.c_str());
			glm::vec4& rectColor = m_Rect.GetComponent<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Color", glm::value_ptr(rectColor));
			ImGui::Separator();
			ImGui::Text("Camera");
			auto& camera = m_Camera.GetComponent<CameraComponent>().Cam;
			float orthoHeight = camera.GetHeight();
			
			if (ImGui::DragFloat("Ortho Height", &orthoHeight))
				camera.SetHeight(orthoHeight);

			ImGui::Separator();
		}

		ImGui::Text("Render Stats:");
		ImGui::Text("  Quad Count: %d", stats.QuadCount);
		ImGui::Text("  Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::Begin("Viewport");

		// Determine whether to consume mouse and keyboard events
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		App::Get().GetImguiLayer()->ConsumeEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		if (viewportSize.x > 0.f && viewportSize.y > 0.f && (m_ViewportSize.x != viewportSize.x || m_ViewportSize.y != viewportSize.y))
		{
			m_ViewportSize = { viewportSize.x, viewportSize.y };
		}
		
		uint32_t fbTexId = m_Framebuffer->GetColorAttachmentId();
		ImGui::Image((void*)fbTexId, 
					 ImVec2((float)m_ViewportSize.x, (float)m_ViewportSize.y),
					 ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
		//ImGui::Image((void*)m_Tex->GetId(), ImVec2(m_Tex->GetWidth(), m_Tex->GetHeight()), ImVec2(0,1), ImVec2(1,0));
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CamCtl.OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressEvent>(EV_BIND_EVENT_CB(EditorLayer::OnKeyPressEvent));
	}

	bool EditorLayer::OnKeyPressEvent(KeyPressEvent& event)
	{
		return false;
	}
}
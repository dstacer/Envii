#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "Sandbox2DLayer.h"

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

Sandbox2DLayer::Sandbox2DLayer()
	: Envii::Layer("Sandbox2DLayer"), 
	  m_CamCtl(1.778f)
{
	m_MapWidth = s_PondWidth;
	m_MapHeight = (uint32_t)strlen(s_MapTiles) / m_MapWidth;
}

Sandbox2DLayer::~Sandbox2DLayer()
{
	
}

void Sandbox2DLayer::OnAttach()
{
	m_Tex = Envii::Texture2D::Create("assets/textures/Kreator.png", 1);
	m_SquareTex = Envii::Texture2D::Create("assets/textures/Checkerboard.png", 2);
	m_SpriteSheet = Envii::Texture2D::Create("assets/textures/RPGpack_sheet.png", 3);
	m_TreeTex = Envii::SubTexture2D::CreateFromIndices(m_SpriteSheet, glm::vec2(2.f, 1.f), 64.f, glm::vec2(1, 2));
	
	for (int i = 0; i < (int)PondTile::NumTiles; i++)
	{
		m_TexMap[i] = Envii::SubTexture2D::CreateFromIndices(m_SpriteSheet, s_PondTileCoords[i], 64.f, glm::vec2(1, 1));
	}
  
	m_CamCtl.SetVerticalExtent(7.2f);
}

void Sandbox2DLayer::OnDetach()
{
	
}

void Sandbox2DLayer::OnUpdate(Envii::TimeStep ts)
{
	EV_PROFILE_FUNCTION();

	m_CamCtl.OnUpdate(ts);

	Envii::Renderer2D::ResetStats();

	Envii::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Envii::RenderCommand::Clear();
	
	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());
	
	Envii::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 10.0f, 10.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_SquareTex, 4.0f, 1);
	for (float x = -10.0f; x < 10.0f; x += 0.1f)
	{
		for (float y = -10.0f; y < 10.0f; y += 0.1f)
		{
			glm::vec4 color = { (x + 6.0f) / 12.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
			Envii::Renderer2D::DrawQuad({ x, y, -0.15f }, { 0.08, 0.08 }, color);
		}
	}
	Envii::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 3.0f, 1.25f }, { 0.1f, 0.2f, 0.8f, 1.0f });
	Envii::Renderer2D::DrawQuadRotate({ 0.0f, 0.0f, -0.1f }, { 3.0f, 1.25f }, { 0.8f, 0.2f, 0.1f, 1.0f }, 45.0f);
	Envii::Renderer2D::DrawQuadRotate({ 0.0f, 0.0f, 0.0f }, { 3.0f, 1.25f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Tex, -45.0f, 2.0f, 1);

	Envii::Renderer2D::EndScene();

#if 0
	Envii::Renderer2D::BeginScene(m_CamCtl.GetCamera());

	for (int y = 0; y < (int)m_MapHeight; y++)
		for (int x = 0; x < (int)m_MapWidth; x++)
		{
			// Subtract 48 (ASCII code for 0) from the map tile value to get the
			// index into the array of subtextures
			int idx = (int)s_MapTiles[y * m_MapWidth + x] - 48;

			Envii::Ref<Envii::SubTexture2D> tile;
			if (m_TexMap.find(idx) != m_TexMap.end())
				tile = m_TexMap[idx];
			else
				tile = m_TreeTex;
			// Since we're iterating through the map from the top down, we need to 
			// invert the y position when drawing, from (mapHeight - 1) to 0
			Envii::Renderer2D::DrawQuad({ x - (m_MapWidth - 1) * 0.5f, - y + (m_MapHeight - 1) * 0.5f, -0.2f }, { 1.f, 1.f }, 
										{ 1.0f, 1.0f, 1.0f, 1.0f },
										tile, 1.0f, 3);
		}

	Envii::Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 1.f, 1.f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_TreeTex, 1.0f, 3);
	
	Envii::Renderer2D::EndScene();
#endif

}

void Sandbox2DLayer::OnImguiRender()
{
	auto stats = Envii::Renderer2D::GetStats();
	
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					Envii::App::Get().Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	
	
	
	ImGui::Begin("Envii Info");
	ImGui::Text("Render Stats:");
	ImGui::Text("  Quad Count: %d", stats.QuadCount);
	ImGui::Text("  Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Envii::Event& event)
{
	m_CamCtl.OnEvent(event);

	Envii::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Envii::KeyPressEvent>(EV_BIND_EVENT_CB(Sandbox2DLayer::OnKeyPressEvent));
}

bool Sandbox2DLayer::OnKeyPressEvent(Envii::KeyPressEvent& event)
{
	return false;
}

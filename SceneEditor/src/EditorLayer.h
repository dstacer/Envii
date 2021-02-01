#pragma once

#include "Envii.h"
#include "Panels/SceneGraphPanel.h"

namespace Envii
{
	enum class PondTile
	{
		Grass = 0,
		ShoreBl,
		ShoreBm,
		ShoreBr,
		ShoreMr,
		ShoreTr,
		ShoreTm,
		ShoreTl,
		ShoreMl,
		ShoreC,
		NumTiles
	};

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(TimeStep) override;
		void OnImguiRender() override;
		void OnEvent(Event& event) override;

	private:
		Ref<Texture2D> m_Tex;
		Ref<Texture2D> m_SquareTex;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TreeTex;

		Ref<FrameBuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;
		Entity m_Rect;
		Entity m_Camera;

		// Panels
		SceneGraphPanel m_ScenePanel;

	};
}
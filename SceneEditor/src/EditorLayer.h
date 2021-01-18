#pragma once

#include "Envii.h"

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
	
		bool OnKeyPressEvent(KeyPressEvent& event);

	private:
		CameraController m_CamCtl;
		Ref<Texture2D> m_Tex;
		Ref<Texture2D> m_SquareTex;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TreeTex;
		std::unordered_map<char, Ref<SubTexture2D>> m_TexMap;
		uint32_t m_MapWidth = 0, m_MapHeight = 0;

		Ref<FrameBuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize;

	};
}
#pragma once

#include "Envii.h"

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

class Sandbox2DLayer : public Envii::Layer
{
public:
	Sandbox2DLayer();
	~Sandbox2DLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Envii::TimeStep) override;
	void OnImguiRender() override;
	void OnEvent(Envii::Event& event) override;
	
	bool OnKeyPressEvent(Envii::KeyPressEvent& event);

private:
	Envii::CameraController m_CamCtl;
	Envii::Ref<Envii::Texture2D> m_Tex;
	Envii::Ref<Envii::Texture2D> m_SquareTex;
	Envii::Ref<Envii::Texture2D> m_SpriteSheet;
	Envii::Ref<Envii::SubTexture2D> m_TreeTex;
	std::unordered_map<char, Envii::Ref<Envii::SubTexture2D>> m_TexMap;
	uint32_t m_MapWidth = 0, m_MapHeight = 0;

};
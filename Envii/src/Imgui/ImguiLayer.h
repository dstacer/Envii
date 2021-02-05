#pragma once

#include "../Core/Layer.h"
#include "../Events/AppEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace Envii
{
	enum Fonts
	{
		OpenSansBold = 0,
		OpenSansReg = 1,
		NumFonts = 2
	};

	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImguiRender() override;
		virtual void OnEvent(Event& event) override;

		void ConsumeEvents(bool shouldConsume) { m_ConsumeEvents = shouldConsume; }
		
		void Begin();
		void End();

		void SetDarkThemColors();
		
	private:
		float m_Time = 0.0f;
		bool m_ConsumeEvents = false;
	};
}
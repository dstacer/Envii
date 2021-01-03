#pragma once

#include "../Core/Layer.h"
#include "../Events/AppEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace Envii
{
	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImguiRender() override;
		
		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};
}
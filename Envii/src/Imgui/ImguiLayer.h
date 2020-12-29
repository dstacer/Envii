#pragma once

#include "../Layer.h"
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
		
		/*virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

	private:
		bool OnMouseButtonPress(MouseButtonPressEvent& e);
		bool OnMouseButtonRelease(MouseButtonReleaseEvent& e);
		bool OnMouseScroll(MouseScrollEvent& e);
		bool OnMouseMove(MouseMoveEvent& e);
		bool OnKeyPress(KeyPressEvent& e);
		bool OnKeyRelease(KeyReleaseEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);*/
	private:
		float m_Time = 0.0f;
	};
}
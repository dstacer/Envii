#pragma once

#include "../Layer.h"

namespace Envii
{
	class ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;
	};
}
#pragma once

#include "Core/Input.h"

namespace Envii
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
		~WindowsInput();

	protected:
		bool IsKeyPressedImpl(int keycode) const override;
		bool IsMouseButtonPressedImpl(int keycode) const override;
		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;
		std::pair<float, float> GetMousePosImpl() const override;
	};
}
#include "evpch.h"

#include "GLFW/glfw3.h"
#include "Core/App.h"
#include "WindowsInput.h"

namespace Envii
{
	Input* Input::s_Instance = new WindowsInput();
	WindowsInput::WindowsInput()
	{
	}

	WindowsInput::~WindowsInput()
	{
	}

	bool WindowsInput::IsKeyPressedImpl(int keycode) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(nativeWindow, keycode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int keycode) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(nativeWindow, keycode);
		return (state == GLFW_PRESS);
	}

	float WindowsInput::GetMouseXImpl() const
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto[x, y] =  GetMousePosImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		double x = 0, y = 0;
		glfwGetCursorPos(nativeWindow, &x, &y); 
		return { (float)x, (float)y };
	}
}
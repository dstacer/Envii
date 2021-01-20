#include "evpch.h"

#include "GLFW/glfw3.h"
#include "Core/App.h"
#include "Core/Input.h"

namespace Envii
{
	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(nativeWindow, keycode);
		return (state == GLFW_PRESS || state == GLFW_REPEAT);
	}

	bool Input::IsMouseButtonPressed(int keycode)
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(nativeWindow, keycode);
		return (state == GLFW_PRESS);
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePos();
		return x;
	}

	float Input::GetMouseY()
	{
		auto[x, y] =  GetMousePos();
		return y;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		double x = 0, y = 0;
		glfwGetCursorPos(nativeWindow, &x, &y); 
		return { (float)x, (float)y };
	}
}
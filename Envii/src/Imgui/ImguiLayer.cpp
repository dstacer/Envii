#include "evpch.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "imgui_impl_opengl3.h"
#include "App.h"
#include "ImguiLayer.h"

namespace Envii
{
	ImguiLayer::ImguiLayer()
		: Layer("ImguiLayer")
	{
	}
	ImguiLayer::~ImguiLayer()
	{
	}
	void ImguiLayer::OnAttach()
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui::StyleColorsDark();
		// Setup Platform/Renderer backends
		ImGui_ImplOpenGL3_Init("#version 330");
	}
	void ImguiLayer::OnDetach()
	{
	}
	void ImguiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		
		float time = glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : 1 / 60.f;
		m_Time = time;
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImguiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnMouseButtonPress));
		dispatcher.Dispatch<MouseButtonReleaseEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnMouseButtonRelease));
		dispatcher.Dispatch<MouseScrollEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnMouseScroll));
		dispatcher.Dispatch<MouseMoveEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnMouseMove));
		dispatcher.Dispatch<KeyPressEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnKeyPress));
		dispatcher.Dispatch<KeyReleaseEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnKeyRelease));
		dispatcher.Dispatch<KeyTypedEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnKeyTyped));
		dispatcher.Dispatch<WindowResizeEvent>(EV_BIND_EVENT_CB(ImguiLayer::OnWindowResize));
	}

	bool ImguiLayer::OnMouseButtonPress(MouseButtonPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = true;

		return false;
	}

	bool ImguiLayer::OnMouseButtonRelease(MouseButtonReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = false;

		return false;
	}

	bool ImguiLayer::OnMouseScroll(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.GetAmountY();
		io.MouseWheelH += e.GetAmountX();

		return false;
	}

	bool ImguiLayer::OnMouseMove(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetMouseX(), e.GetMouseY());

		return false;
	}

	bool ImguiLayer::OnKeyPress(KeyPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImguiLayer::OnKeyRelease(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImguiLayer::OnKeyTyped(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());

		return false;
	}

	bool ImguiLayer::OnWindowResize(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		return false;
	}

}
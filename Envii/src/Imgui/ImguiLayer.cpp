#include "evpch.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
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
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		// Setup ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		App& app = App::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImguiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::OnImguiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImguiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight()); 
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
	/*void ImguiLayer::OnUpdate()
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
	}*/

}
#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Render/GraphicsContext.h"
#include "Core/Window.h"

namespace Envii
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		void OnUpdate() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallback& callback) override
		{
			m_Data.Callback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		
		struct WindowData
		{
			std::string Title; 
			uint32_t Width;
			uint32_t Height;
			bool VSync;
			EventCallback Callback;
		};

		WindowData m_Data;
	};
}

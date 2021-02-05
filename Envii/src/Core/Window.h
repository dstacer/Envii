#pragma once

//#include "evpch.h"
#include "Core.h"
#include "../Events/Event.h"

namespace Envii
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(std::string title = "Envii App", uint32_t width = 1600, uint32_t height = 900)
			: Title(title),
			  Width(width),
			  Height(height){ }
	};

	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& cb) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		// Get the native window, regardless of underlying implementation
		virtual void* GetNativeWindow() const = 0;

		// Basic platform-independent Window abstraction, subclassed
		// per platform
		static Window* Create(const WindowProps& props = WindowProps());
	};
}

#pragma once

#include "Render/GraphicsContext.h"

struct GLFWwindow;

namespace Envii
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}
#include "evpch.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "OpenGLContext.h"

namespace Envii
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window) 
	{
		EV_CORE_ASSERT(m_Window, "GLFW window handle is null.");
	}

	void OpenGLContext::Init()
	{
		// Get our graphics context
		glfwMakeContextCurrent(m_Window);

		// Load OpenGL procs
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EV_CORE_ASSERT(status, "GLAD failed to load GL lib.");

		std::cout << "OpenGL Info:" << std:: endl
		<< "   Vendor: " << glGetString(GL_VENDOR)		<< std::endl
	    << "   Renderer: " << glGetString(GL_RENDERER)	<< std::endl 
		<< "   Version: " << glGetString(GL_VERSION)	<< std::endl
		<< "   GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
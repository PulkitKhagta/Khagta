#include "kgpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Khagta{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		KG_CORE_ASSERT(windowHandle, "window Hnadle is Null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KG_CORE_ASSERT(status, "Failed to initialize Glad!");

		KG_CORE_INFO("OpenGL Renderer:");
		KG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
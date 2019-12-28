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

		KG_CORE_INFO("OpenGL Info:");
		KG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef KG_ENABLE_ASSERTS

		int versionMajor;

		int versionMinor;

		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);

		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);



		KG_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Khagta requires at least OpenGL version 4.5!");

#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
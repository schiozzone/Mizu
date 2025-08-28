#include "mzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Mizu {

	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
	{
		MZ_CORE_ASSERT(window, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		MZ_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		MZ_CORE_INFO("OpenGL Info:");
		MZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		MZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		MZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#ifdef MZ_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		MZ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Al least OpenGL version 4.5 is required!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		MZ_PROFILE_FUNCTION();
		glfwSwapBuffers(m_Window);
	}
}
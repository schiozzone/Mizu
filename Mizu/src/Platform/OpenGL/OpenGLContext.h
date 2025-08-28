#pragma once

#include "Mizu/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Mizu {

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
#include "mzpch.h"
#include "Mizu/Renderer/GraphicsContext.h"

#include "Mizu/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Mizu {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			MZ_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		MZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
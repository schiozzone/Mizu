#include "mzpch.h"
#include "Mizu/Renderer/RenderCommand.h"

namespace Mizu {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
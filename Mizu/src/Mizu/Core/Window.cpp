#include "mzpch.h"
#include "Mizu/Core/Window.h"

#ifdef MZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Mizu {

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef MZ_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			MZ_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}

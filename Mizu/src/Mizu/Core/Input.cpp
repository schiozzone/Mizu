#include "mzpch.h"
#include "Mizu/Core/Input.h"

#ifdef MZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Mizu {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef MZ_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			MZ_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
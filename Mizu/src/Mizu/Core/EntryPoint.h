#pragma once
#include "Mizu/Core/Core.h"

#ifdef MZ_PLATFORM_WINDOWS

extern Mizu::Application* Mizu::CreateApplication();

int main(int argc, char** argv)
{
	Mizu::Log::Init();

	MZ_PROFILE_BEGIN_SESSION("Startup", "Mizu-StartupProfile.json");
	auto app = Mizu::CreateApplication();
	MZ_PROFILE_END_SESSION();

	MZ_PROFILE_BEGIN_SESSION("Runtime", "Mizu-RuntimeProfile.json");
	app->Run();
	MZ_PROFILE_END_SESSION();

	MZ_PROFILE_BEGIN_SESSION("Shutdown", "Mizu-ShutdownProfile.json");
	delete app;
	MZ_PROFILE_END_SESSION();
}

#endif
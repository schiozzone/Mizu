workspace "Mizu"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories rel to root
IncludeDir = {}
IncludeDir["GLFW"] = "Mizu/vendor/GLFW/include"
IncludeDir["Glad"] = "Mizu/vendor/Glad/include"
IncludeDir["ImGui"] = "Mizu/vendor/imgui"
IncludeDir["glm"] = "Mizu/vendor/glm"
IncludeDir["stb_image"] = "Mizu/vendor/stb_image"

group "Dependencies"
	include "Mizu/vendor/GLFW"
	include "Mizu/vendor/Glad"
	include "Mizu/vendor/imgui"

group ""

project "Mizu"
	location "Mizu"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mzpch.h"
	pchsource "Mizu/src/mzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/stb_image.h",
		"%{prj.name}/vendor/stb_image/stb_image.cpp",
	}

	filter "files:%{prj.name}/src/imgui/**.cpp"
		flags {"NoPCH"}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MZ_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Mizu/vendor/spdlog/include",
		"Mizu/src",
		"Mizu/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mizu"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MZ_DIST"
		runtime "Release"
		optimize "On"
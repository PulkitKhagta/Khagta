workspace "Khagta"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directories)
IncludeDir = {}
IncludeDir["GLFW"] = "Khagta/vendor/GLFW/include"
IncludeDir["Glad"] = "Khagta/vendor/Glad/include"
IncludeDir["imGui"] = "Khagta/vendor/imgui"
IncludeDir["glm"] = "Khagta/vendor/glm"
IncludeDir["stp_image"] = "Khagta/vendor/stp_image"

include "Khagta/vendor/GLFW"
include "Khagta/vendor/Glad"
include "Khagta/vendor/imgui"

project "Khagta"
	location "Khagta"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "kgpch.h"
	pchsource "Khagta/src/kgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stp_image/**.h",
		"%{prj.name}/vendor/stp_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stp_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"


		defines
		{
		"KG_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "KG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KG_RELEASE"
		runtime "Release"
		optimize "on"
	  
	filter "configurations:Dist"
		defines "KG_Dist"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Khagta/vendor/spdlog/include",
		"Khagta/src",
		"Khagta/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Khagta"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "KG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KG_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "KG_Dist"
		runtime "Release"
		optimize "on"

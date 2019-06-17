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

include "Khagta/vendor/GLFW"
include "Khagta/vendor/Glad"
include "Khagta/vendor/imgui"

project "Khagta"
	location "Khagta"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "kgpch.h"
	pchsource "Khagta/src/kgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imGui}",
		"%{IncludeDir.glm}"
	}

	 links
	 {
		"GLFW",
		"Glad",
		"imGui",
		"opengl32.lib"
	 }

	 filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


		defines
		{
		"KG_PLATFORM_WINDOWS",
		"KG_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
		}

		--postbuildcommands
		--{
		--	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		--}

	filter "configurations:Debug"
		defines "KG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "KG_RELEASE"
		runtime "Release"
		optimize "On"
      
	filter "configurations:Dist"
		defines "KG_Dist"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
	 	"Khagta"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


		defines
		{
		"KG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "KG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "KG_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "KG_Dist"
		
		runtime "Release"
		optimize "On"
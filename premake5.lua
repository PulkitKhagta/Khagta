workspace "Khagta"
	architecture "x64"


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

include "Khagta/vendor/GLFW"
include "Khagta/vendor/Glad"

project "Khagta"
	location "Khagta"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "kgpch.h"
	pchsource "Khagta/src/kgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	 links
	 {
		"GLFW",
		"Glad",
		"opengl32.lib"
	 }

	 filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"


		defines
		{
		"KG_PLATFORM_WINDOWS",
		"KG_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
		}

		--postbuildcommands
		--{
		--	("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		--}

	filter "configurations:Debug"
		defines "KG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "KG_RELEASE"
		buildoptions "/MD"
		optimize "On"
      
	filter "configurations:Dist"
		defines "KG_Dist"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Khagta/src"
	}

	links
	{
	 	"Khagta"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"


		defines
		{
		"KG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "KG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "KG_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "KG_Dist"
		buildoptions "/MD"
		optimize "On"
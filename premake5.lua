workspace "Miros"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	--Include directories to root folder (solution directory) 
	IncludeDir = {}
	IncludeDir["GLFW"] = "Miros/vendor/GLFW/include"
	IncludeDir["GLAD"] = "Miros/vendor/GLAD/include"

	--包含项目
	include "Miros/vendor/GLFW"
	include "Miros/vendor/GLAD"


project "Miros"
	location "Miros"
	kind "SharedLib"
	language "C++"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")


	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}
	includedirs{
		"%{prj.name}/src/",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}
	links{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines{
			"_DEBUG",
			"_CONSOLE",
			"_WINDLL",
			"MRS_PLATFORM_WINDOWS",
			"MRS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .."/SandBox")
		}

	-- 过滤器 Debug配置 仅适用于Debug
	filter "configurations:Debug"
		defines "MRS_DEBUG"
		symbols "On"
		buildoptions "/MDd"
	-- 过滤器 Release配置
	filter "configurations:Release"
		defines "MRS_RELEASE"
		optimize "On"
		buildoptions "/MD"
	-- 过滤器 Dist配置
	filter "configurations:Dist"
		defines "MRS_DIST"
		optimize "On"
		buildoptions "/MD"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}
	includedirs
	{
		"Miros/vendor/spdlog/include",
		"Miros/src"
	}
	links
	{
		"Miros"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"


		defines
		{
			"MRS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "MRS_DEBUG"
		symbols "On"
		buildoptions "/MDd"
	filter "configurations:Release"
		defines "MRS_RELEASE"
		optimize "On"
		buildoptions "/MD"
	filter "configurations:Dist"
		defines "MRS_DIST"
		optimize "On" 
		buildoptions "/MD"
-- premake5.lua
workspace "Envii"
   architecture "x86_64" 
   configurations { "Debug", "Release", "Dist" }
   startproject "Sandbox"

-- Output directory for binaries and intermediates
outputdir = "%{cfg.buildcfg}/%{cfg.architecture}/"

-- Table of include directories for external dependencies
extIncludeDirs = {}
extIncludeDirs["glfw"] = "%{wks.name}/thirdparty/glfw/include"
extIncludeDirs["glad"] = "%{wks.name}/thirdparty/glad/include"
extIncludeDirs["imgui"] = "%{wks.name}/thirdparty/imgui"
extIncludeDirs["glm"] = "%{wks.name}/thirdparty/glm"

group "Dependencies"
	include "Envii/thirdparty/glfw"
	include "Envii/thirdparty/glad"
	include "Envii/thirdparty/imgui"
    
group ""

-- This includes the premake5.lua files in the subproject dirs
include "Envii/thirdparty/glfw"
include "Envii/thirdparty/glad"
include "Envii/thirdparty/imgui"

project "Envii"
   location "Envii"
   kind "StaticLib"
   staticruntime "on"
   language "C++"
   cppdialect "C++17"
   bindir = "bin/" .. outputdir .. "/"
   targetdir (bindir .. "%{prj.name}")
   objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

   pchheader "evpch.h"
   pchsource "%{prj.name}/src/evpch.cpp"

   defines
   {
        "_CRT_SECURE_NO_WARNINGS"
   }

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   includedirs 
   { 
        "%{prj.location}/src",
        "%{wks.location}/Envii/thirdparty/spdlog/include",
        "%{extIncludeDirs.glfw}",
        "%{extIncludeDirs.glad}",
        "%{extIncludeDirs.imgui}",
        "%{extIncludeDirs.imgui}/backends",
        "%{extIncludeDirs.glm}"
   }

   links 
   {
        "Envii/thirdparty/glfw/" .. bindir .. "glfw.lib",
        "Envii/thirdparty/glad/" .. bindir .. "glad.lib",
        "Envii/thirdparty/imgui/" .. bindir .. "imgui.lib",
        "opengl32.lib"
   }

   filter "system:windows"
      systemversion "latest"
      defines "EV_PLATFORM_WINDOWS"

      postbuildcommands 
      {
         --("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "Sandbox")
      }
   
   filter "configurations:Debug"
      defines { "EV_DEBUG", "_DEBUG" }
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines { "EV_RELEASE", "NDEBUG" }
      runtime "Release"
      optimize "on"

   filter "configurations:Dist"
      defines { "EV_DIST", "NDEBUG" }
      runtime "Release"
      optimize "on"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"
   targetdir ("bin/" .. outputdir .. "%{prj.name}")
   objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   includedirs 
   { "%{wks.location}/Envii/src/Client",
     "%{wks.location}/Envii/thirdparty/spdlog/include", 
     "%{wks.location}/Envii/thirdparty/glm", 
     "%{wks.location}/Envii/thirdparty/imgui" 
   }
   
   links "Envii" 
   
   filter "system:windows"
      systemversion "latest"
      defines "EV_PLATFORM_WINDOWS"

   filter "configurations:Debug"
      defines { "EV_DEBUG", "_DEBUG" }
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines { "EV_RELEASE", "NDEBUG" }
      runtime "Release"
      optimize "on"

   filter "configurations:Dist"
      defines { "EV_DIST", "NDEBUG" }
      runtime "Release"
      optimize "on"

-- premake5.lua
workspace "Envii"
   architecture "x86_64" 
   configurations { "Debug", "Release", "Dist" }

-- Output directory for binaries and intermediates
outputdir = "%{cfg.buildcfg}/%{cfg.architecture}/"

-- Table of include directories for external dependencies
extIncludeDirs = {}
extIncludeDirs["glfw"] = "%{wks.name}/thirdparty/glfw/include"
extIncludeDirs["glad"] = "%{wks.name}/thirdparty/glad/include"

-- This includes the premake5.lua file in the glfw project
include "Envii/thirdparty/glfw"
include "Envii/thirdparty/glad"

project "Envii"
   location "Envii"
   kind "StaticLib"
   language "C++"
   bindir = "bin/" .. outputdir .. "/"
   targetdir (bindir .. "%{prj.name}")
   objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

   pchheader "evpch.h"
   pchsource "%{prj.name}/src/evpch.cpp"

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   includedirs 
   { 
        "%{prj.location}/src",
        "%{wks.location}/Envii/thirdparty/spdlog/include",
        "%{extIncludeDirs.glfw}",
        "%{extIncludeDirs.glad}"
   }

   links 
   {
        "Envii/thirdparty/glfw/" .. bindir .. "glfw.lib",
        "Envii/thirdparty/glad/" .. bindir .. "glad.lib",
        "opengl32.lib"
   }

   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines "EV_PLATFORM_WINDOWS"

      postbuildcommands 
      {
         ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "Sandbox")
      }
   
   filter "configurations:Debug"
      defines { "EV_DEBUG", "_DEBUG", "_CONSOLE" }
      symbols "On"

   filter "configurations:Release"
      defines { "EV_RELEASE", "NDEBUG", "_CONSOLE" }
      optimize "On"

   filter "configurations:Dist"
      defines { "EV_DIST", "NDEBUG", "_CONSOLE" }
      optimize "On"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   targetdir ("bin/" .. outputdir .. "%{prj.name}")
   objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   includedirs { "%{wks.location}/Envii/src/Client",
                 "%{wks.location}/Envii/thirdparty/spdlog/include" 
               }
   
   links "Envii" 
   
   filter "system:windows"
      cppdialect "C++17"
      staticruntime "On"
      systemversion "latest"
      defines "EV_PLATFORM_WINDOWS"

   filter "configurations:Debug"
      defines { "EV_DEBUG", "_DEBUG", "_CONSOLE" }
      symbols "On"

   filter "configurations:Release"
      defines { "EV_RELEASE", "NDEBUG", "_CONSOLE" }
      optimize "On"

   filter "configurations:Dist"
      defines { "EV_DIST", "NDEBUG", "_CONSOLE" }
      optimize "On"
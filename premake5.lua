-- premake5.lua
workspace "Envii"
   architecture "x86_64" 
   configurations { "Debug", "Release", "Dist" }
   startproject "SceneEditor"

-- Output directory for binaries and intermediates
outputdir = "%{cfg.buildcfg}/%{cfg.architecture}/"

-- Table of include directories for external dependencies
extIncludeDirs = {}
extIncludeDirs["glad"] = "%{wks.name}/thirdparty/glad/include"
extIncludeDirs["glfw"] = "%{wks.name}/thirdparty/glfw/include"
extIncludeDirs["glm"] = "%{wks.name}/thirdparty/glm"
extIncludeDirs["imgui"] = "%{wks.name}/thirdparty/imgui"
extIncludeDirs["stb_image"] = "%{wks.name}/thirdparty/stb_image"
extIncludeDirs["entt"] = "%{wks.name}/thirdparty/entt/include"
extIncludeDirs["yaml_cpp"] = "%{wks.name}/thirdparty/yaml-cpp/include"
extIncludeDirs["imguizmo"] = "%{wks.name}/thirdparty/ImGuizmo"

group "Dependencies"
	include "Envii/thirdparty/glfw"
	include "Envii/thirdparty/glad"
	include "Envii/thirdparty/imgui"
    include "Envii/thirdparty/yaml-cpp"
    
group ""

-- This includes the premake5.lua files in the subproject dirs
include "Envii/thirdparty/glfw"
include "Envii/thirdparty/glad"
include "Envii/thirdparty/imgui"
include "Envii/thirdparty/yaml-cpp"

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

   files { "%{prj.name}/src/**.h", 
           "%{prj.name}/src/**.cpp",
           "%{prj.name}/thirdparty/stb_image/**.*",
           "%{prj.name}/thirdparty/ImGuizmo/ImGuizmo.h",
           "%{prj.name}/thirdparty/ImGuizmo/ImGuizmo.cpp"
         }

   includedirs 
   { 
        "%{prj.location}/src",
        "%{wks.location}/Envii/thirdparty/spdlog/include",
        "%{extIncludeDirs.glfw}",
        "%{extIncludeDirs.glad}",
        "%{extIncludeDirs.imgui}",
        "%{extIncludeDirs.imgui}/backends",
        "%{extIncludeDirs.glm}",
        "%{extIncludeDirs.stb_image}",
        "%{extIncludeDirs.entt}",
        "%{extIncludeDirs.yaml_cpp}",
        "%{extIncludeDirs.imguizmo}"
   }

   links 
   {
        "Envii/thirdparty/glfw/" .. bindir .. "glfw.lib",
        "Envii/thirdparty/glad/" .. bindir .. "glad.lib",
        "Envii/thirdparty/imgui/" .. bindir .. "imgui.lib",
        "Envii/thirdparty/yaml-cpp/" .. bindir .. "yaml.lib",
        "opengl32.lib"
   }

   --filter "files:thirdparty/ImGuizmo/**.cpp"
    --  flags "NoPCH" 

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
   { 
     "%{wks.location}/Envii/src/Client",
     "%{wks.location}/Envii/thirdparty/spdlog/include", 
     "%{extIncludeDirs.glm}", 
     "%{extIncludeDirs.imgui}",
     "%{extIncludeDirs.entt}"
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

project "SceneEditor"
   location "SceneEditor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"
   targetdir ("bin/" .. outputdir .. "%{prj.name}")
   objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   includedirs 
   { 
     "src",
     "%{wks.location}/Envii/src/Client",
     "%{wks.location}/Envii/thirdparty/spdlog/include", 
     "%{extIncludeDirs.glm}", 
     "%{extIncludeDirs.imgui}",
     "%{extIncludeDirs.entt}",
     "%{extIncludeDirs.yaml_cpp}",
     "%{extIncludeDirs.imguizmo}"
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
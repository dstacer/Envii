project "glad"
   kind "StaticLib"
   language "C"
   targetdir ("bin/" .. outputdir)
   objdir ("Intermediate/" .. outputdir)

   files 
   { 
		"include/glad/glad.h", 
		"include/KHR/khrplatform.h",
        "src/glad.c"
   }

   includedirs { "include" }

   filter "system:windows"
      staticruntime "On"
      systemversion "latest"
   
   filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

   filter "configurations:Release"
		runtime "Release"
		optimize "on"

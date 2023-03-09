--
-- GENIe solution to build the EDK project.
-- Ivan Sancho, Escuela Superior de Arte y Tecnologia (ESAT) Valencia, 2022/23
-- Graphic Programming
--
-- All rights are reserved.
--
--

PROJ_DIR = path.getabsolute("./../")

solution("EDK_Workspace_" .. _ACTION)
  location(PROJ_DIR .. "/build/")
  language "C++"
  kind "ConsoleApp"
  startproject "PR_Demo_Workspace"

  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }

  configurations {
    "Debug",
    "Release"
  }

  configuration { "Debug" }
    defines {
      "DEBUG",
    }
    flags {
      "Symbols",
      "ExtraWarnings",
    }
    targetsuffix "_d"

  configuration { "Release" }
    defines {
      "NDEBUG",
    }
    flags {
      "Optimize",
      "OptimizeSize",
      "No64BitChecks",
      "NoPCH",
    }

  projects_names = {
    "PR_Demo_Workspace",
  }

--[[************************* PROJECT GENERATOR FUNCTION *************************]]--
  for i, prj in ipairs(projects_names) do
    project(prj)
      location (PROJ_DIR .. "/build/" .. prj .. "/" .. _ACTION)
      platforms {
        "x32",
        "Native",
      }
      includedirs {
        path.join(PROJ_DIR, "./include/"),
        path.join(PROJ_DIR, "./include/dev"),
        path.join(PROJ_DIR, "./deps/EDK/include/"),
        path.join(PROJ_DIR, "./deps/Perlin/include/"),
        path.join(PROJ_DIR, "./deps/Perlin/src/"),
        path.join(PROJ_DIR, "./deps/STB/include/"),
      }
      files {
        path.join(PROJ_DIR, "./include/*.h"),
        path.join(PROJ_DIR, "./include/dev/*.h"),
        path.join(PROJ_DIR, "./src/*.cc"),
        path.join(PROJ_DIR, "./src/dev/*.cc"),
        path.join(PROJ_DIR, "./deps/EDK/include/EDK3/*.h"),
        path.join(PROJ_DIR, "./deps/EDK/include/EDK3/dev/*.h"),
        path.join(PROJ_DIR, "./deps/EDK/include/ESAT/*.h"),
        path.join(PROJ_DIR, "./deps/EDK/include/ESAT_extra/*.h"),
        path.join(PROJ_DIR, "./deps/Perlin/include/Perlin/*.h"),
        path.join(PROJ_DIR, "./deps/Perlin/src/*.cpp"),
        path.join(PROJ_DIR, "./deps/STB/include/*.h"),
      }

      libdirs { path.join(PROJ_DIR, "./deps/EDK/lib/EDK/x32"), }

      configuration { "Debug", "x32" }
        targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Debug"))
        targetsuffix "_d"
        links { path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_d"),
                path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_extra_d"),
                "OpenGL32",
                "winmm" }
      configuration { "Release", "x32" }
        targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Release"))
        links { path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT"),
                path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_extra"),
                "OpenGL32",
                "winmm" }
	end

  project "PR_Demo_Workspace"
  	files {
  	  path.join(PROJ_DIR, "./tests/main.cc"),
    }

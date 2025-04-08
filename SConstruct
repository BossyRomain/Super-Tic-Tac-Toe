#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/", "src/board/", "src/players/", "src/players/ai_heuristics"])
sources = []
for dir in [
    "src/*.cpp",
    "src/board/*.cpp",
    "src/players/*.cpp",
    "src/players/ai_heuristics/*.cpp",
]:
    sources.extend(Glob(dir))

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "super_tic_tac_toe/bin/lib_super_tic_tac_toe.{}.{}.framework/lib_super_tic_tac_toe.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "super_tic_tac_toe/bin/lib_super_tic_tac_toe.{}.{}.simulator.a".format(
                env["platform"], env["target"]
            ),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "super_tic_tac_toe/bin/lib_super_tic_tac_toe.{}.{}.a".format(
                env["platform"], env["target"]
            ),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "super_tic_tac_toe/bin/lib_super_tic_tac_toe{}{}".format(
            env["suffix"], env["SHLIBSUFFIX"]
        ),
        source=sources,
    )

Default(library)

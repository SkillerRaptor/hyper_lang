#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15)
project(HyperLang LANGUAGES CXX)

#-------------------------------------------------------------------------------------------
# Modules
#-------------------------------------------------------------------------------------------
include(Development/CMake/StandardProjectSettings.cmake)

#-------------------------------------------------------------------------------------------
# Project Libraries
#-------------------------------------------------------------------------------------------
add_library(ProjectOptions INTERFACE)
target_compile_features(ProjectOptions INTERFACE cxx_std_17)

add_library(ProjectWarnings INTERFACE)

#-------------------------------------------------------------------------------------------
# Standard Settings
#-------------------------------------------------------------------------------------------
include(Development/CMake/Cache.cmake)

include(Development/CMake/CompilerWarnings.cmake)
enable_warnings(ProjectWarnings)

include(Development/CMake/Sanitizers.cmake)
enable_sanitizers(ProjectOptions)

include(Development/CMake/Doxygen.cmake)
enable_doxygen()

include(Development/CMake/StaticAnalyzers.cmake)

#-------------------------------------------------------------------------------------------
# Conan
#-------------------------------------------------------------------------------------------
set(CONAN_LIBRARIES
        fmt/8.0.1)

set(CONAN_OPTIONS
        )

include(Development/CMake/Conan.cmake)
run_conan()

#-------------------------------------------------------------------------------------------
# Source
#-------------------------------------------------------------------------------------------
add_subdirectory(Source)

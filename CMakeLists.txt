#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)
project(HyperLang)

#-------------------------------------------------------------------------------------------
# Standard Settings
#-------------------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#-------------------------------------------------------------------------------------------
# Variables
#-------------------------------------------------------------------------------------------
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(BUILD_TYPE "Debug")
else ()
    set(BUILD_TYPE "Release")
endif ()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(COMPILER "Clang")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(COMPILER "GNU")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set(COMPILER "MSVC")
endif ()

#-------------------------------------------------------------------------------------------
# Flags
#-------------------------------------------------------------------------------------------
if ("${COMPILER}" STREQUAL "MSVC")
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP8")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D_CRT_SECURE_NO_DEPRECATE /D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /D_SCL_SECURE_NO_DEPRECATE /D_SCL_SECURE_NO_WARNINGS")
endif ()

if ("${BUILD_TYPE}" STREQUAL "Debug")
    if ("${COMPILER}" STREQUAL "Clang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
    elseif ("${COMPILER}" STREQUAL "GNU")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
    elseif ("${COMPILER}" STREQUAL "MSVC")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Od /Zi")
    endif ()
elseif ("${BUILD_TYPE}" STREQUAL "Release")
    if ("${COMPILER}" STREQUAL "Clang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -m64 -mavx2 -mfma -ffast-math")
    elseif ("${COMPILER}" STREQUAL "GNU")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -m64 -mavx2 -mfma -ffast-math")
    elseif ("${COMPILER}" STREQUAL "MSVC")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /arch:AVX2 /fp:fast")
    endif ()
endif ()

if ("${COMPILER}" STREQUAL "Clang")
	set(WARNING_FLAGS -Wall -Wextra -Wpedantic -fms-extensions)
elseif ("${COMPILER}" STREQUAL "GNU")
	set(WARNING_FLAGS -Wall -Wextra -Wpedantic)
elseif ("${COMPILER}" STREQUAL "MSVC")
	set(WARNING_FLAGS /W4)
endif ()

#-------------------------------------------------------------------------------------------
# HyperLang
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/ast.c
        src/expressions.c
        src/generator.c
		src/lexer.c
		src/logger.c
		src/main.c
        src/statements.c
		src/token.c)

set(HEADERS
        include/ast.h
        include/expressions.h
        include/generator.h
		include/lexer.h
		include/logger.h
        include/statements.h
		include/token.h)

add_executable(HyperLang ${SOURCES} ${HEADERS})
target_compile_options(HyperLang PRIVATE ${WARNING_FLAGS})
target_include_directories(HyperLang PRIVATE ./include)

add_custom_command(
        TARGET HyperLang
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/test ${CMAKE_CURRENT_BINARY_DIR}/test)

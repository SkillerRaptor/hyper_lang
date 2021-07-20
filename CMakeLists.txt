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

#-------------------------------------------------------------------------------------------
# HyperLang
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.c
        src/logger.c)

set(HEADERS
        include/logger.h)

add_executable(HyperLang ${SOURCES} ${HEADERS})
target_include_directories(HyperLang PRIVATE ./include)
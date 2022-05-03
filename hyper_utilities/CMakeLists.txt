#-------------------------------------------------------------------------------------------
# Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# hyper_utilities
#-------------------------------------------------------------------------------------------
set(SOURCES
		src/hyper_utilities/args_parser.cpp
		src/hyper_utilities/assertions.cpp
		src/hyper_utilities/profiler.cpp
		src/hyper_utilities/utilities.cpp)

add_library(hyper_utilities STATIC ${SOURCES})
target_link_libraries(
		hyper_utilities
		PRIVATE
		project_options
		project_warnings)
target_include_directories(
		hyper_utilities
		PUBLIC
		include)

if (ENABLE_PROFILING)
	target_compile_definitions(hyper_utilities PUBLIC HYPER_PROFILING=1)
endif()

#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# hyper test
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        src/hyper/formatter.cpp
        src/hyper/tester.cpp)

add_executable(hyper_test ${SOURCES})
add_dependencies(hyper_test hyper)
target_link_libraries(
        hyper_test
        PRIVATE
        project_options
        project_warnings)
target_include_directories(
        hyper_test
        PUBLIC
        include)

add_custom_command(
        TARGET hyper_test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:hyper_test>/tests)

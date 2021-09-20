#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Hyper
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/logger.c
        src/main.c
        src/utils.c)

set(HEADERS
        include/colors.h
        include/config.h
        include/logger.h
        include/utils.h)

hyperlang_define_executable(hyper)
add_custom_command(
        TARGET hyper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:hyper>/tests)

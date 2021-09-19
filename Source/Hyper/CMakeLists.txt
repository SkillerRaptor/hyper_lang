#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Hyper
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        )

set(HEADERS
        )

hyperlang_define_executable(Hyper)
target_link_libraries(
        Hyper
        PRIVATE
        CONAN_PKG::llvm-core)

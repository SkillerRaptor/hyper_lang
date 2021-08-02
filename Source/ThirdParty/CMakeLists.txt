#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------------------------------------------
# ThirdParty
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# fmt
#-------------------------------------------------------------------------------------------
add_subdirectory(fmt)

#-------------------------------------------------------------------------------------------
# LLVM
#-------------------------------------------------------------------------------------------
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

find_library(LLD_ELF NAMES lldELF.a liblldELF.a PATHS ${LLVM_LIBRARY_DIRS})
llvm_map_components_to_libnames(LLVM_LIBS
        AllTargetsAsmParsers
        AllTargetsDescs
        AllTargetsDisassemblers
        AllTargetsInfos
        AllTargetsCodeGens
        Analysis
        BitReader
        Core
        InstCombine
        MC
        MCDisassembler
        Object
        ScalarOpts
        Support
        Target
        TransformUtils
        native
        nativecodegen
        AsmPrinter
        Linker
        LTO
        WindowsManifest
        DebugInfoPDB
        LibDriver
        Option
        IrReader)

add_library(llvm INTERFACE)
target_compile_definitions(llvm INTERFACE ${LLVM_DEFINITIONS})
target_include_directories(llvm INTERFACE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm INTERFACE ${LLVM_LIBS} ${LLD_ELF})

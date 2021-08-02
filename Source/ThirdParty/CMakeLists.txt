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
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Libraries located in: ${LLVM_LIBRARY_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(LLVM_LINK_COMPONENTS
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

llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})

find_library(LLD_COFF NAMES lldCOFF.a liblldCOFF.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_COMMON NAMES lldCommon.a liblldCommon.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_CORE NAMES lldCore.a liblldCore.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_WASM NAMES lldWasm.a liblldWasm.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_MINGW NAMES lldMinGW.a liblldMinGW.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_ELF NAMES lldELF.a liblldELF.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_DRIVER NAMES lldDriver.a liblldDriver.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_READER_WRITER NAMES lldReaderWriter.a liblldReaderWriter.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_MACHO NAMES lldMachO.a liblldMachO.a PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_YAML NAMES lldYAML.a liblldYAML.a PATHS ${LLVM_LIBRARY_DIRS})

set(lld_libs
        ${LLD_COFF}
        ${LLD_COMMON}
        ${LLD_WASM}
        ${LLD_MINGW}
        ${LLD_ELF}
        ${LLD_DRIVER}
        ${LLD_READER_WRITER}
        ${LLD_MACHO}
        ${LLD_YAML}
        ${LLD_CORE})

message(STATUS "Found LLD ${lld_libs}")

add_library(llvm INTERFACE)
target_compile_definitions(llvm INTERFACE ${LLVM_DEFINITIONS})
target_include_directories(llvm INTERFACE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm INTERFACE ${llvm_libs} ${lld_libs})

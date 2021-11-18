#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Third Party
#-------------------------------------------------------------------------------------------
find_package(LLVM REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

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

find_library(LLD_COFF NAMES lldCOFF.a liblldCOFF.a lldCOFF.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_COMMON NAMES lldCommon.a liblldCommon.a lldCommon.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_CORE NAMES lldCore.a liblldCore.a lldCore.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_WASM NAMES lldWasm.a liblldWasm.a lldWasm.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_MINGW NAMES lldMinGW.a liblldMinGW.a lldMinGW.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_ELF NAMES lldELF.a liblldELF.a lldELF.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_DRIVER NAMES lldDriver.a liblldDriver.a lldDriver.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_READER_WRITER NAMES lldReaderWriter.a liblldReaderWriter.a lldReaderWriter.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_MACHO NAMES lldMachO.a liblldMachO.a lldMachO.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_YAML NAMES lldYAML.a liblldYAML.a lldYAML.lib PATHS ${LLVM_LIBRARY_DIRS})

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

add_library(llvm INTERFACE)
target_compile_definitions(
        llvm
        INTERFACE
        ${LLVM_DEFINITIONS})
target_link_libraries(
        llvm
        INTERFACE
        ${llvm_libs}
        ${lld_libs})
target_include_directories(
        llvm
        INTERFACE
        ${LLVM_INCLUDE_DIRS})

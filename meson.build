#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Meson Info
#-------------------------------------------------------------------------------------------
project('HyperLang', 'c', license: 'MIT')

sources = ['src/logger.c', 'src/main.c', 'src/utils.c']
headers = ['include/logger.h', 'include/utils.h']

include = include_directories('include')
executable('HyperLang', sources, headers, include_directories: include)
#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Meson Info
#-------------------------------------------------------------------------------------------
project('HyperLang', 'c', license: 'MIT')

sources = ['src/main.c', 'src/logger.c']
headers = ['include/logger.h']

include = include_directories('include')
executable('HyperLang', sources, headers, include_directories: include)
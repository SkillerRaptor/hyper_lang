#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Meson Info
#-------------------------------------------------------------------------------------------
project('HyperLang', 'c', license: 'MIT')

sources = ['src/lexer.c', 'src/logger.c', 'src/main.c']
headers = ['include/lexer.h', 'include/logger.h', 'include/token.h']

include = include_directories('include')
executable('HyperLang', sources, headers, include_directories: include)

/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_LOGGER_H_
#define HYPERLANG_LOGGER_H_

void info(const char* format, ...);
void warning(const char* format, ...);
void error(const char* format, ...);
void fatal(const char* format, ...);
void debug(const char* format, ...);

#endif // HYPERLANG_LOGGER_H_

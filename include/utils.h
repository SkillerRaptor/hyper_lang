/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_UTILS_H_
#define HYPERLANG_UTILS_H_

char* read_file_source(const char* file_name);
void free_file_source(char* buffer);

#endif // HYPERLANG_UTILS_H_
/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPER_UTILS_H_
#define HYPER_UTILS_H_

int hyper_read_file(const char* file_name, char** buffer);

int hyper_duplicate_string(const char* source, char** destination);

void hyper_terminate_compilation(void);

#endif //HYPER_UTILS_H_

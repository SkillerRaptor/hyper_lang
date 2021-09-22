/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPER_LOGGER_H_
#define HYPER_LOGGER_H_

void print(const char* format, ...);

void hyper_info(const char* format, ...);
void hyper_error(const char* format, ...);
void hyper_fatal_error(const char* format, ...);

#endif //HYPER_LOGGER_H_

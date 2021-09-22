/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "logger.h"

#include "colors.h"

#include <stdarg.h>
#include <stdio.h>

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif

void print(const char* format, ...)
{
	printf("%s", HYPER_FORMAT_RESET);
	
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void hyper_info(const char* format, ...)
{
	printf("%s%shyper: %sinfo: %s", HYPER_FORMAT_BOLD, HYPER_COLOR_WHITE, HYPER_COLOR_LIGHT_GREEN, HYPER_FORMAT_RESET);
	
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void hyper_error(const char* format, ...)
{
	printf("%s%shyper: %serror: %s", HYPER_FORMAT_BOLD, HYPER_COLOR_WHITE, HYPER_COLOR_LIGHT_RED, HYPER_FORMAT_RESET);
	
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void hyper_fatal_error(const char* format, ...)
{
	printf("%s%shyper: %sfatal error: %s", HYPER_FORMAT_BOLD, HYPER_COLOR_WHITE, HYPER_COLOR_RED, HYPER_FORMAT_RESET);
	
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif

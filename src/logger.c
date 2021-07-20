/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <logger.h>
#include <stdarg.h>
#include <stdio.h>

#define FORMAT_RESET "\033[0m"
#define FORMAT_BOLD "\033[1m"

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_AQUA "\033[36m"
#define COLOR_LIGHT_RED "\033[91m"

static void log(const char* format, va_list args)
{
	vprintf(format, args);
}

void info(const char* format, ...)
{
	printf(FORMAT_BOLD "hypercc: " COLOR_GREEN "info: " FORMAT_RESET);

	va_list args;
	va_start(args, format);
	log(format, args);
	va_end(args);
}

void warning(const char* format, ...)
{
	printf(FORMAT_BOLD "hypercc: " COLOR_YELLOW "warning: " FORMAT_RESET);

	va_list args;
	va_start(args, format);
	log(format, args);
	va_end(args);
}

void error(const char* format, ...)
{
	printf(FORMAT_BOLD "hypercc: " COLOR_LIGHT_RED "error: " FORMAT_RESET);

	va_list args;
	va_start(args, format);
	log(format, args);
	va_end(args);
}

void fatal(const char* format, ...)
{
	printf(FORMAT_BOLD "hypercc: " COLOR_RED "fatal error: " FORMAT_RESET);

	va_list args;
	va_start(args, format);
	log(format, args);
	va_end(args);
}

void debug(const char* format, ...)
{
	printf(FORMAT_BOLD "hypercc: " COLOR_AQUA "debug: " FORMAT_RESET);

	va_list args;
	va_start(args, format);
	log(format, args);
	va_end(args);
}
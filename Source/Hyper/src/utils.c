/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "utils.h"

#include "logger.h"

#include <stdlib.h>

void terminate_compilation()
{
	print("compilation terminated.\n");
	exit(1);
}

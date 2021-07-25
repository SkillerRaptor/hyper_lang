/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_TYPES_H_
#define HYPERLANG_TYPES_H_

enum
{
	PRIMITIVE_TYPE_NONE,
	PRIMITIVE_TYPE_CHAR,
	PRIMITIVE_TYPE_INT,
	PRIMITIVE_TYPE_VOID
};

int type_compatible(int* left_type, int* right_type, int only_right);
int token_to_primitive_type(int token_type);
const char *primitive_type_to_string(int type);

#endif // HYPERLANG_TYPES_H_

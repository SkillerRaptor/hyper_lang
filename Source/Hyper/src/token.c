/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "token.h"

#include <stddef.h>

const char* token_type_to_string(int token_type)
{
	switch (token_type)
	{
	case TOKEN_TYPE_EOF:
		return "TOKEN_TYPE_EOF";
	case TOKEN_TYPE_PLUS:
		return "TOKEN_TYPE_PLUS";
	case TOKEN_TYPE_MINUS:
		return "TOKEN_TYPE_MINUS";
	case TOKEN_TYPE_STAR:
		return "TOKEN_TYPE_STAR";
	case TOKEN_TYPE_SLASH:
		return "TOKEN_TYPE_SLASH";
	case TOKEN_TYPE_NUMERIC_LITERAL:
		return "TOKEN_TYPE_NUMERIC_LITERAL";
	default:
		break;
	}
	
	return NULL;
}

/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "types.h"

#include "ast.h"
#include "logger.h"
#include "token.h"
#include "utils.h"

int type_compatible(int* left_type, int* right_type, int only_right)
{
	if ((*left_type == PRIMITIVE_TYPE_VOID) || (*right_type == PRIMITIVE_TYPE_VOID))
	{
		return 0;
	}

	if (*left_type == *right_type)
	{
		*left_type = 0;
		*right_type = 0;
		return 1;
	}

	if ((*left_type == PRIMITIVE_TYPE_CHAR) && (*right_type == PRIMITIVE_TYPE_INT))
	{
		*left_type = AST_OPERATION_WIDEN;
		*right_type = 0;
		return 1;
	}
	
	if ((*left_type == PRIMITIVE_TYPE_INT) && (*right_type == PRIMITIVE_TYPE_CHAR))
	{
		if (only_right)
		{
			return 0;
		}

		*left_type = 0;
		*right_type = AST_OPERATION_WIDEN;
		return 1;
	}

	*right_type = 0;
	*right_type = 0;
	return 1;
}

int token_to_primitive_type(int token_type)
{
	switch (token_type)
	{
	case TOKEN_TYPE_CHAR:
		return PRIMITIVE_TYPE_CHAR;
	case TOKEN_TYPE_INT:
		return PRIMITIVE_TYPE_INT;
	case TOKEN_TYPE_VOID:
		return PRIMITIVE_TYPE_VOID;
	default:
		break;
	}

	fatal("illegal token type\n");
	exit_program();

	return -1;
}

const char* primitive_type_to_string(int type)
{
	switch (type)
	{
	case PRIMITIVE_TYPE_NONE:
		return "PRIMITIVE_TYPE_NONE";
	case PRIMITIVE_TYPE_CHAR:
		return "PRIMITIVE_TYPE_CHAR";
	case PRIMITIVE_TYPE_INT:
		return "PRIMITIVE_TYPE_INT";
	case PRIMITIVE_TYPE_VOID:
		return "PRIMITIVE_TYPE_VOID";
	default:
		break;
	}

	return "undefined primitive type";
}

/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "generator.h"

#include "logger.h"
#include "symbol_table.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

static FILE* file = NULL;
static int current_register = 1;

void init_generator(const char* file_name)
{
	file = fopen(file_name, "w");
	if (file == NULL)
	{
		fatal("failed to open file\n");
		exit_program();

		return;
	}
}

void free_generator(void)
{
	fclose(file);
}

static int allocate_register(void)
{
	return current_register++;
}

static int store_value(int value)
{
	int value_register = allocate_register();
	fprintf(file, "  %%%u = alloca i32, align 4\n", value_register);
	fprintf(file, "  store i32 %u, i32* %%%u, align 4\n", value, value_register);
	return value_register;
}

static int store_register(int reg)
{
	int value_register = allocate_register();
	fprintf(file, "  %%%u = alloca i32, align 4\n", value_register);
	fprintf(file, "  store i32 %%%u, i32* %%%u, align 4\n", reg, value_register);
	return value_register;
}

static int load_register(int value_register)
{
	int reg = allocate_register();
	fprintf(file, "  %%%u = load i32, i32* %%%u, align 4\n", reg, value_register);
	return reg;
}

static int store_global_register(int reg, const char* identifier)
{
	int value_register = load_register(reg);
	fprintf(file, "  store i32 %%%u, i32* @%s, align 4\n", value_register, identifier);
	return reg;
}

static int load_global_register(const char* identifier)
{
	int reg = allocate_register();
	fprintf(file, "  %%%u = load i32, i32* @%s, align 4\n", reg, identifier);

	int value_register = store_register(reg);
	return value_register;
}

static int generate_add(int first_register, int second_register)
{
	int first_value_register = load_register(first_register);
	int second_value_register = load_register(second_register);

	int value = allocate_register();
	fprintf(file, "  %%%u = add nsw i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = store_register(value);
	return value_register;
}

static int generate_subtract(int first_register, int second_register)
{
	int first_value_register = load_register(first_register);
	int second_value_register = load_register(second_register);

	int value = allocate_register();
	fprintf(file, "  %%%u = sub nsw i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = store_register(value);
	return value_register;
}

static int generate_multiplication(int first_register, int second_register)
{
	int first_value_register = load_register(first_register);
	int second_value_register = load_register(second_register);

	int value = allocate_register();
	fprintf(file, "  %%%u = mul nsw i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = store_register(value);
	return value_register;
}

static int generate_division(int first_register, int second_register)
{
	int first_value_register = load_register(first_register);
	int second_value_register = load_register(second_register);

	int value = allocate_register();
	fprintf(file, "  %%%u = udiv i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = store_register(value);
	return value_register;
}

static int generate_compare(int first_register, int second_register, const char* operation)
{
	int first_value = load_register(first_register);
	int second_value = load_register(second_register);
	
	int value_register = allocate_register();
	fprintf(file, "  %%%u = icmp %s i32 %%%u, %%%u\n", value_register, operation, first_value, second_value);

	int second_value_register = allocate_register();
	fprintf(file, "  %%%u = zext i1 %%%u to i32\n", second_value_register, value_register);

	int compare_register = store_register(second_value_register);
	return compare_register;
}

static int generate_equal(int first_register, int second_register)
{
	return generate_compare(first_register, second_register, "eq");
}

static int generate_not_equal(int first_register, int second_register)
{
	return generate_compare(first_register, second_register, "ne");
}

static int generate_less_than(int first_register, int second_register)
{
	return generate_compare(first_register, second_register, "slt");
}

static int generate_greater_than(int first_register, int second_register)
{
	return generate_compare(first_register, second_register, "sgt");
}

static int generate_less_equal(int first_register, int second_register)
{
	return generate_compare(first_register, second_register, "sle");
}

static int generate_greater_equal(int first_register, int second_register)
{
	return generate_compare(first_register, second_register, "sge");
}

int generate_print_register(int value_register)
{
	int value = load_register(value_register);
	int reg = allocate_register();
	fprintf(file, "  %%%u = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%%u)\n", reg, value);
	return reg;
}

void generate_pre_code(void)
{
	fprintf(file, "@.str = private unnamed_addr constant [4 x i8] c\"%%i\\0A\\00\", align 1\n");
	fprintf(file, "\n");
	fprintf(file, "define i32 @main() #0 {\n");
}

void generate_post_code(void)
{
	fprintf(file, "  ret i32 0\n");
	fprintf(file, "}\n");
	fprintf(file, "\n");
	fprintf(file, "declare i32 @printf(i8*, ...) #1\n");
	fprintf(file, "\n");

	for (int i = 0; i < 1024; ++i)
	{
		if (strcmp(get_symbol(i)->name, "\0") == 0)
		{
			continue;
		}

		fprintf(file, "@%s = global i32 0, align 4\n", get_symbol(i)->name);
	}
}

int generate_ast(struct ast* ast, int reg)
{
	int left_register = 0;
	if (ast->left)
	{
		left_register = generate_ast(ast->left, -1);
	}

	int right_register = 0;
	if (ast->right)
	{
		right_register = generate_ast(ast->right, left_register);
	}

	switch (ast->type)
	{
	case AST_TYPE_ADD:
		return generate_add(left_register, right_register);
	case AST_TYPE_SUBTRACT:
		return generate_subtract(left_register, right_register);
	case AST_TYPE_MULTIPLY:
		return generate_multiplication(left_register, right_register);
	case AST_TYPE_DIVIDE:
		return generate_division(left_register, right_register);
	case AST_TYPE_INT_LITERAL:
		return store_value(ast->value.int_value);
	case AST_TYPE_L_VALUE:
		return store_global_register(reg, get_symbol(ast->value.identifier)->name);
	case AST_TYPE_IDENTIFIER:
		return load_global_register(get_symbol(ast->value.identifier)->name);
	case AST_TYPE_ASSIGN:
		return right_register;
	case AST_TYPE_EQUAL:
		return generate_equal(left_register, right_register);
	case AST_TYPE_NOT_EQUAL:
		return generate_not_equal(left_register, right_register);
	case AST_TYPE_LESS_THAN:
		return generate_less_than(left_register, right_register);
	case AST_TYPE_GREATER_THAN:
		return generate_greater_than(left_register, right_register);
	case AST_TYPE_LESS_EQUAL:
		return generate_less_equal(left_register, right_register);
	case AST_TYPE_GREATER_EQUAL:
		return generate_greater_equal(left_register, right_register);
	default:
		break;
	}

	fatal("unknown ast operation\n");
	exit_program();

	return -1;
}

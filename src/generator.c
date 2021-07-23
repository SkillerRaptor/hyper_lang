/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <generator.h>
#include <logger.h>
#include <symbol_table.h>
#include <stdio.h>
#include <string.h>

static FILE* file;
static int current_register;

static int generator_allocate_register(void)
{
	return current_register++;
}

static int generator_generate_store_value(int value)
{
	int value_register = generator_allocate_register();
	fprintf(file, "  %%%u = alloca i32, align 4\n", value_register);
	fprintf(file, "  store i32 %u, i32* %%%u, align 4\n", value, value_register);
	return value_register;
}

static int generator_generate_store_register(int reg)
{
	int value_register = generator_allocate_register();
	fprintf(file, "  %%%u = alloca i32, align 4\n", value_register);
	fprintf(file, "  store i32 %%%u, i32* %%%u, align 4\n", reg, value_register);
	return value_register;
}

static int generator_generate_load(int value_register)
{
	int reg = generator_allocate_register();
	fprintf(file, "  %%%u = load i32, i32* %%%u, align 4\n", reg, value_register);
	return reg;
}

static int generator_generate_add(int first_register, int second_register)
{
	int first_value_register = generator_generate_load(first_register);
	int second_value_register = generator_generate_load(second_register);

	int value = generator_allocate_register();
	fprintf(file, "  %%%u = add nsw i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = generator_generate_store_register(value);
	return value_register;
}

static int generator_generate_subtract(int first_register, int second_register)
{
	int first_value_register = generator_generate_load(first_register);
	int second_value_register = generator_generate_load(second_register);

	int value = generator_allocate_register();
	fprintf(file, "  %%%u = sub nsw i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = generator_generate_store_register(value);
	return value_register;
}

static int generator_generate_multiplication(int first_register, int second_register)
{
	int first_value_register = generator_generate_load(first_register);
	int second_value_register = generator_generate_load(second_register);

	int value = generator_allocate_register();
	fprintf(file, "  %%%u = mul nsw i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = generator_generate_store_register(value);
	return value_register;
}

static int generator_generate_division(int first_register, int second_register)
{
	int first_value_register = generator_generate_load(first_register);
	int second_value_register = generator_generate_load(second_register);

	int value = generator_allocate_register();
	fprintf(file, "  %%%u = udiv i32 %%%u, %%%u\n", value, first_value_register, second_value_register);

	int value_register = generator_generate_store_register(value);
	return value_register;
}
static int generator_generate_load_global(const char* identifier)
{
	int reg = generator_allocate_register();
	fprintf(file, "  %%%u = load i32, i32* @%s, align 4\n", reg, identifier);
	
	int value_register = generator_generate_store_register(reg);
	return value_register;
}

static int generator_generate_store_global(int reg, const char* identifier)
{
	int value_register = generator_generate_load(reg);
	fprintf(file, "  store i32 %%%u, i32* @%s, align 4\n", value_register, identifier);
	return reg;
}

void generator_init(const char* file_name)
{
	file = fopen(file_name, "w");
	current_register = 1;
}

void generator_free(void)
{
	fclose(file);
}

int generator_generate_ast(struct ast* ast, int reg)
{
	int left_register = 0;
	if (ast->left)
	{
		left_register = generator_generate_ast(ast->left, -1);
	}

	int right_register = 0;
	if (ast->right)
	{
		right_register = generator_generate_ast(ast->right, left_register);
	}
	
	switch (ast->type)
	{
	case AST_TYPE_ADD:
		return generator_generate_add(left_register, right_register);
	case AST_TYPE_SUBTRACT:
		return generator_generate_subtract(left_register, right_register);
	case AST_TYPE_MULTIPLY:
		return generator_generate_multiplication(left_register, right_register);
	case AST_TYPE_DIVIDE:
		return generator_generate_division(left_register, right_register);
	case AST_TYPE_INT_LITERAL:
		return generator_generate_store_value(ast->value.int_value);
	case AST_TYPE_IDENTIFIER:
		return generator_generate_load_global(symbol_table[ast->value.identifier].name);
	case AST_TYPE_L_VALUE:
		return generator_generate_store_global(reg, symbol_table[ast->value.identifier].name);
	case AST_TYPE_ASSIGN:
		return right_register;
	default:
		break;
	}

	fatal("generator.c: unknown ast operation %u\n", ast->type);
	return -1;
}

void generator_generate_pre_code(void)
{
	fprintf(file, "@.str = private unnamed_addr constant [4 x i8] c\"%%i\\0A\\00\", align 1\n");
	fprintf(file, "\n");
	fprintf(file, "define i32 @main() #0 {\n");
}

void generator_generate_post_code(void)
{
	fprintf(file, "  ret i32 0\n");
	fprintf(file, "}\n");
	fprintf(file, "\n");
	fprintf(file, "declare i32 @printf(i8*, ...) #1\n");
	fprintf(file, "\n");

	for (int i = 0; i < 1024; ++i)
	{
		if (strcmp(symbol_table[i].name, "\0") != 0)
		{
			fprintf(file, "@%s = global i32 0, align 4\n", symbol_table[i].name);
		}
	}
}

int generator_generate_print_int(int value_register)
{
	int value = generator_generate_load(value_register);
	int reg = generator_allocate_register();
	fprintf(file, "  %%%u = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%%u)\n", reg, value);
	return reg;
}

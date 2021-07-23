/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <generator.h>
#include <logger.h>
#include <stdio.h>

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

static int generator_generate_ast(struct ast* ast)
{
	int left_register = 0;
	if (ast->left)
	{
		left_register = generator_generate_ast(ast->left);
	}

	int right_register = 0;
	if (ast->right)
	{
		right_register = generator_generate_ast(ast->right);
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
		return generator_generate_store_value(ast->int_value);
	default:
		break;
	}

	fatal("interpreter.c: unknown ast operation %u\n", ast->type);
	return -1;
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

static void generator_generate_pre_code(void)
{
	fprintf(file, "@.str = private unnamed_addr constant [4 x i8] c\"%%i\\0A\\00\", align 1\n");
	fprintf(file, "\n");
	fprintf(file, "define i32 @main() #0 {\n");
}

static void generator_generate_post_code(void)
{
	fprintf(file, "  ret i32 0\n");
	fprintf(file, "}\n");
	fprintf(file, "\n");
	fprintf(file, "declare i32 @printf(i8*, ...) #1\n");
}

static int generator_generate_print_int(int value_register)
{
	int value = generator_generate_load(value_register);
	int reg = generator_allocate_register();
	fprintf(file, "  %%%u = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%%u)\n", reg, value);
	return reg;
}

void generator_generate_code(struct ast* ast)
{
	generator_generate_pre_code();
	int reg = generator_generate_ast(ast);
	generator_generate_print_int(reg);
	generator_generate_post_code();
}

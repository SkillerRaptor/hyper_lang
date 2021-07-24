/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "generator.h"

#include "logger.h"
#include "symbol_table.h"
#include "utils.h"

#include <llvm-c/Core.h>

#include <string.h>

static const char* output_file_name = NULL;

static LLVMContextRef context;
static LLVMModuleRef module;
static LLVMBuilderRef builder;

static LLVMTypeRef int_1_type;
static LLVMTypeRef int_8_type;
static LLVMTypeRef int_8_type_pointer;
static LLVMTypeRef int_32_type;
static LLVMTypeRef int_32_type_pointer;

static LLVMValueRef printf_function;
static LLVMValueRef printf_format;

static LLVMValueRef main_function;

void init_generator(const char* file_name)
{
	output_file_name = file_name;

	context = LLVMContextCreate();
	module = LLVMModuleCreateWithNameInContext(file_name, context);
	builder = LLVMCreateBuilderInContext(context);

	int_1_type = LLVMInt1TypeInContext(context);
	int_8_type = LLVMInt8TypeInContext(context);
	int_8_type_pointer = LLVMPointerType(int_8_type, 0);
	int_32_type = LLVMInt32TypeInContext(context);
	int_32_type_pointer = LLVMPointerType(int_32_type, 0);
}

void free_generator(void)
{
	LLVMDisposeBuilder(builder);
	LLVMDisposeModule(module);
	LLVMContextDispose(context);
}

static LLVMValueRef store_value(int value)
{
	LLVMValueRef reg = LLVMBuildAlloca(builder, int_32_type, "");
	LLVMBuildStore(builder, LLVMConstInt(int_32_type, value, 0), reg);
	return reg;
}

static LLVMValueRef store_register(LLVMValueRef value_register)
{
	LLVMValueRef reg = LLVMBuildAlloca(builder, int_32_type, "");
	LLVMBuildStore(builder, value_register, reg);
	return reg;
}

static LLVMValueRef load_register(LLVMValueRef value_register)
{
	LLVMValueRef reg = LLVMBuildLoad(builder, value_register, "");
	return reg;
}

static LLVMValueRef store_global_register(LLVMValueRef reg, const char* identifier)
{
	LLVMValueRef global_register = LLVMGetNamedGlobal(module, identifier);
	LLVMValueRef value = load_register(reg);
	LLVMBuildStore(builder, value, global_register);
	return reg;
}

static LLVMValueRef load_global_register(const char* identifier)
{
	LLVMValueRef global_register = LLVMGetNamedGlobal(module, identifier);
	LLVMValueRef reg = LLVMBuildLoad(builder, global_register, "");

	LLVMValueRef value_register = store_register(reg);
	return value_register;
}

static LLVMValueRef generate_add(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value_register = load_register(first_register);
	LLVMValueRef second_value_register = load_register(second_register);

	LLVMValueRef value = LLVMBuildAdd(builder, first_value_register, second_value_register, "");

	LLVMValueRef value_register = store_register(value);
	return value_register;
}

static LLVMValueRef generate_subtract(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value_register = load_register(first_register);
	LLVMValueRef second_value_register = load_register(second_register);

	LLVMValueRef value = LLVMBuildSub(builder, first_value_register, second_value_register, "");

	LLVMValueRef value_register = store_register(value);
	return value_register;
}

static LLVMValueRef generate_multiplication(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value_register = load_register(first_register);
	LLVMValueRef second_value_register = load_register(second_register);

	LLVMValueRef value = LLVMBuildMul(builder, first_value_register, second_value_register, "");

	LLVMValueRef value_register = store_register(value);
	return value_register;
}

static LLVMValueRef generate_division(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value_register = load_register(first_register);
	LLVMValueRef second_value_register = load_register(second_register);

	LLVMValueRef value = LLVMBuildUDiv(builder, first_value_register, second_value_register, "");

	LLVMValueRef value_register = store_register(value);
	return value_register;
}

static LLVMBasicBlockRef create_label()
{
	LLVMBasicBlockRef label = LLVMAppendBasicBlockInContext(context, main_function, "");
	return label;
}

static void generate_label(LLVMBasicBlockRef label)
{
	LLVMPositionBuilderAtEnd(builder, label);
}

static void generate_jump(LLVMBasicBlockRef label)
{
	LLVMBuildBr(builder, label);
}

static LLVMValueRef generate_if(struct ast* ast)
{
	LLVMBasicBlockRef true_label = create_label();
	LLVMBasicBlockRef false_label = ast->right ? create_label() : NULL;
	LLVMBasicBlockRef end_label = create_label();

	LLVMBasicBlockRef labels[] = {
		true_label,
		ast->right ? false_label : end_label
	};

	generate_ast(ast->left, NULL, labels, ast->type);

	generate_label(true_label);
	generate_ast(ast->middle, NULL, NULL, ast->type);
	generate_jump(end_label);

	if (ast->right)
	{
		generate_label(false_label);
		generate_ast(ast->right, NULL, NULL, ast->type);
		generate_jump(end_label);
	}

	generate_label(end_label);

	return NULL;
}

static LLVMValueRef generate_compare_and_set(int type, LLVMValueRef first_register, LLVMValueRef second_register)
{
	if (type < AST_TYPE_EQUAL || type > AST_TYPE_GREATER_EQUAL)
	{
		fatal("bad ast type\n");
		exit_program();

		return NULL;
	}
	
	LLVMIntPredicate predicate = 0;
	switch (type)
	{
	case AST_TYPE_EQUAL:
		predicate = LLVMIntEQ;
		break;
	case AST_TYPE_NOT_EQUAL:
		predicate = LLVMIntNE;
		break;
	case AST_TYPE_LESS_THAN:
		predicate = LLVMIntSLT;
		break;
	case AST_TYPE_GREATER_THAN:
		predicate = LLVMIntSGT;
		break;
	case AST_TYPE_LESS_EQUAL:
		predicate = LLVMIntSLE;
		break;
	case AST_TYPE_GREATER_EQUAL:
		predicate = LLVMIntSGT;
		break;
	default:
		break;
	}
	
	LLVMValueRef first_value = load_register(first_register);
	LLVMValueRef second_value = load_register(second_register);
	LLVMValueRef compare_register = LLVMBuildICmp(builder, predicate, first_value, second_value, "");
	LLVMValueRef value = LLVMBuildZExt(builder, compare_register, int_32_type, "");
	LLVMValueRef value_register = store_register(value);
	return value_register;
}

static void generate_compare_and_jump(
	int type,
	LLVMValueRef first_register,
	LLVMValueRef second_register,
	LLVMBasicBlockRef first_label,
	LLVMBasicBlockRef second_label)
{
	if (type < AST_TYPE_EQUAL || type > AST_TYPE_GREATER_EQUAL)
	{
		fatal("bad ast type\n");
		exit_program();

		return;
	}

	LLVMIntPredicate predicate = 0;
	switch (type)
	{
	case AST_TYPE_EQUAL:
		predicate = LLVMIntEQ;
		break;
	case AST_TYPE_NOT_EQUAL:
		predicate = LLVMIntNE;
		break;
	case AST_TYPE_LESS_THAN:
		predicate = LLVMIntSLT;
		break;
	case AST_TYPE_GREATER_THAN:
		predicate = LLVMIntSGT;
		break;
	case AST_TYPE_LESS_EQUAL:
		predicate = LLVMIntSLE;
		break;
	case AST_TYPE_GREATER_EQUAL:
		predicate = LLVMIntSGT;
		break;
	default:
		break;
	}
	
	LLVMValueRef first_value = load_register(first_register);
	LLVMValueRef second_value = load_register(second_register);
	LLVMValueRef compare_register = LLVMBuildICmp(builder, predicate, first_value, second_value, "");
	LLVMBuildCondBr(builder, compare_register, first_label, second_label);
}

static LLVMValueRef generate_print_register(LLVMValueRef value_register)
{
	LLVMValueRef printf_function_args[] = {
		printf_format,
		load_register(value_register)
	};

	LLVMValueRef reg = LLVMBuildCall(builder, printf_function, printf_function_args, 2, "");
	return reg;
}

void add_global_variable(const char* identifier)
{
	LLVMValueRef global = LLVMAddGlobal(module, int_32_type, identifier);
	LLVMSetInitializer(global, LLVMConstInt(int_32_type, 0, 0));
}

void generate_pre_code(void)
{
	LLVMTypeRef printf_function_args_type[] = { int_8_type_pointer };
	LLVMTypeRef printf_function_type = LLVMFunctionType(int_32_type, printf_function_args_type, 0, 1);
	printf_function = LLVMAddFunction(module, "printf", printf_function_type);

	LLVMTypeRef main_function_type = LLVMFunctionType(int_32_type, NULL, 0, 0);
	main_function = LLVMAddFunction(module, "main", main_function_type);

	LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, main_function, "entry");
	LLVMPositionBuilderAtEnd(builder, entry);

	printf_format = LLVMBuildGlobalString(builder, "%i\n", ".str");
}

void generate_post_code(void)
{
	LLVMBuildRet(builder, LLVMConstInt(int_32_type, 0, 0));
}

void generate_code(void)
{
	LLVMPrintModuleToFile(module, output_file_name, NULL);
}

LLVMValueRef generate_ast(
	struct ast* ast,
	LLVMValueRef reg,
	LLVMBasicBlockRef* labels,
	int parent_type)
{
	switch (ast->type)
	{
	case AST_TYPE_IF:
		return generate_if(ast);
	case AST_TYPE_GLUE:
		generate_ast(ast->left, NULL, NULL, ast->type);
		generate_ast(ast->right, NULL, NULL, ast->type);
		return NULL;
	default:
		break;
	}

	LLVMValueRef left_register = NULL;
	if (ast->left)
	{
		left_register = generate_ast(ast->left, NULL, NULL, ast->type);
	}

	LLVMValueRef right_register = NULL;
	if (ast->right)
	{
		right_register = generate_ast(ast->right, left_register, NULL, ast->type);
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
	case AST_TYPE_EQUAL:
	case AST_TYPE_NOT_EQUAL:
	case AST_TYPE_LESS_THAN:
	case AST_TYPE_GREATER_THAN:
	case AST_TYPE_LESS_EQUAL:
	case AST_TYPE_GREATER_EQUAL:
		if (parent_type == AST_TYPE_IF)
		{
			generate_compare_and_jump(ast->type, left_register, right_register, labels[0], labels[1]);
			return NULL;
		}

		return generate_compare_and_set(ast->type, left_register, right_register);
	case AST_TYPE_INT_LITERAL:
		return store_value(ast->value.int_value);
	case AST_TYPE_L_VALUE:
		return store_global_register(reg, get_symbol(ast->value.identifier)->name);
	case AST_TYPE_IDENTIFIER:
		return load_global_register(get_symbol(ast->value.identifier)->name);
	case AST_TYPE_ASSIGN:
		return right_register;
	case AST_TYPE_PRINT:
		generate_print_register(left_register);
		return NULL;
	default:
		break;
	}

	fatal("unknown ast operation\n");
	exit_program();

	return NULL;
}

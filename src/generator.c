/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "generator.h"

#include "logger.h"
#include "symbol_table.h"
#include "types.h"
#include "utils.h"

#include <llvm-c/Core.h>

#include <string.h>

static const char* output_file_name = NULL;

static LLVMContextRef context;
static LLVMModuleRef module;
static LLVMBuilderRef builder;

static LLVMTypeRef int_8_type;
static LLVMTypeRef int_8_type_pointer;
static LLVMTypeRef int_32_type;
static LLVMTypeRef int_32_type_pointer;

static LLVMValueRef printf_function;
static LLVMValueRef printf_format;

static LLVMValueRef current_function;

void init_generator(const char* file_name)
{
	output_file_name = file_name;
	
	context = LLVMContextCreate();
	module = LLVMModuleCreateWithNameInContext(file_name, context);
	builder = LLVMCreateBuilderInContext(context);
	
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

static LLVMValueRef store_value(int value, LLVMTypeRef type)
{
	LLVMValueRef reg = LLVMBuildAlloca(builder, type, "");
	LLVMBuildStore(builder, LLVMConstInt(type, value, 0), reg);
	return reg;
}

static LLVMValueRef store_register(LLVMValueRef value_register, LLVMTypeRef type)
{
	LLVMValueRef reg = LLVMBuildAlloca(builder, type, "");
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
	LLVMTypeRef global_type = LLVMTypeOf(global_register);
	
	LLVMValueRef value = load_register(reg);
	LLVMValueRef bit_cast_value = LLVMBuildZExtOrBitCast(builder, value, LLVMGetElementType(global_type), "");
	LLVMBuildStore(builder, bit_cast_value, global_register);
	return reg;
}

static LLVMValueRef load_global_register(const char* identifier)
{
	LLVMValueRef global_register = LLVMGetNamedGlobal(module, identifier);
	LLVMTypeRef global_type = LLVMTypeOf(global_register);
	
	LLVMValueRef reg = LLVMBuildLoad(builder, global_register, "");
	
	LLVMValueRef value_register = store_register(reg, LLVMGetElementType(global_type));
	return value_register;
}

static LLVMValueRef generate_add(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value = load_register(first_register);
	LLVMTypeRef first_type = LLVMTypeOf(first_value);
	
	LLVMValueRef second_value = load_register(second_register);
	LLVMTypeRef second_type = LLVMTypeOf(second_value);
	
	LLVMValueRef cast_second_value = second_value;
	if (first_type == int_32_type && second_type != int_32_type)
	{
		cast_second_value = LLVMBuildZExtOrBitCast(builder, second_value, int_32_type, "");
	}
	
	LLVMValueRef cast_first_value = first_value;
	if (second_type == int_32_type && first_type != int_32_type)
	{
		cast_first_value = LLVMBuildZExtOrBitCast(builder, first_value, int_32_type, "");
	}
	
	LLVMValueRef value = LLVMBuildAdd(builder, cast_first_value, cast_second_value, "");
	LLVMTypeRef value_type = LLVMTypeOf(value);
	
	LLVMValueRef value_register = store_register(value, value_type);
	return value_register;
}

static LLVMValueRef generate_subtract(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value = load_register(first_register);
	LLVMTypeRef first_type = LLVMTypeOf(first_value);
	
	LLVMValueRef second_value = load_register(second_register);
	LLVMTypeRef second_type = LLVMTypeOf(second_value);
	
	LLVMValueRef cast_second_value = second_value;
	if (first_type == int_32_type && second_type != int_32_type)
	{
		cast_second_value = LLVMBuildZExtOrBitCast(builder, second_value, int_32_type, "");
	}
	
	LLVMValueRef cast_first_value = first_value;
	if (second_type == int_32_type && first_type != int_32_type)
	{
		cast_first_value = LLVMBuildZExtOrBitCast(builder, first_value, int_32_type, "");
	}
	
	LLVMValueRef value = LLVMBuildSub(builder, cast_first_value, cast_second_value, "");
	LLVMTypeRef value_type = LLVMTypeOf(value);
	
	LLVMValueRef value_register = store_register(value, value_type);
	return value_register;
}

static LLVMValueRef generate_multiplication(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value = load_register(first_register);
	LLVMTypeRef first_type = LLVMTypeOf(first_value);
	
	LLVMValueRef second_value = load_register(second_register);
	LLVMTypeRef second_type = LLVMTypeOf(second_value);
	
	LLVMValueRef cast_second_value = second_value;
	if (first_type == int_32_type && second_type != int_32_type)
	{
		cast_second_value = LLVMBuildZExtOrBitCast(builder, second_value, int_32_type, "");
	}
	
	LLVMValueRef cast_first_value = first_value;
	if (second_type == int_32_type && first_type != int_32_type)
	{
		cast_first_value = LLVMBuildZExtOrBitCast(builder, first_value, int_32_type, "");
	}
	
	LLVMValueRef value = LLVMBuildMul(builder, cast_first_value, cast_second_value, "");
	LLVMTypeRef value_type = LLVMTypeOf(value);
	
	LLVMValueRef value_register = store_register(value, value_type);
	return value_register;
}

static LLVMValueRef generate_division(LLVMValueRef first_register, LLVMValueRef second_register)
{
	LLVMValueRef first_value = load_register(first_register);
	LLVMTypeRef first_type = LLVMTypeOf(first_value);
	
	LLVMValueRef second_value = load_register(second_register);
	LLVMTypeRef second_type = LLVMTypeOf(second_value);
	
	LLVMValueRef cast_second_value = second_value;
	if (first_type == int_32_type && second_type != int_32_type)
	{
		cast_second_value = LLVMBuildZExtOrBitCast(builder, second_value, int_32_type, "");
	}
	
	LLVMValueRef cast_first_value = first_value;
	if (second_type == int_32_type && first_type != int_32_type)
	{
		cast_first_value = LLVMBuildZExtOrBitCast(builder, first_value, int_32_type, "");
	}
	
	LLVMValueRef value = LLVMBuildUDiv(builder, cast_first_value, cast_second_value, "");
	LLVMTypeRef value_type = LLVMTypeOf(value);
	
	LLVMValueRef value_register = store_register(value, value_type);
	return value_register;
}

static LLVMBasicBlockRef create_label()
{
	LLVMBasicBlockRef label = LLVMAppendBasicBlockInContext(context, current_function, "");
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

static void generate_if(struct ast* ast)
{
	LLVMBasicBlockRef true_label = create_label();
	LLVMBasicBlockRef false_label = ast->right ? create_label() : NULL;
	LLVMBasicBlockRef end_label = create_label();
	
	LLVMBasicBlockRef labels[] = {
		true_label,
		ast->right ? false_label : end_label
	};
	
	generate_ast(ast->left, NULL, labels, ast->operation);
	
	generate_label(true_label);
	generate_ast(ast->middle, NULL, NULL, ast->operation);
	generate_jump(end_label);
	
	if (ast->right)
	{
		generate_label(false_label);
		generate_ast(ast->right, NULL, NULL, ast->operation);
		generate_jump(end_label);
	}
	
	generate_label(end_label);
}

static void generate_while(struct ast* ast)
{
	LLVMBasicBlockRef start_label = create_label();
	LLVMBasicBlockRef body_label = create_label();
	LLVMBasicBlockRef end_label = create_label();
	LLVMBasicBlockRef labels[] = {
		body_label,
		end_label
	};
	
	generate_jump(start_label);
	
	generate_label(start_label);
	generate_ast(ast->left, NULL, labels, ast->operation);
	
	generate_label(body_label);
	generate_ast(ast->right, NULL, NULL, ast->operation);
	generate_jump(start_label);
	
	generate_label(end_label);
}

static LLVMValueRef generate_compare_and_set(int type, LLVMValueRef first_register, LLVMValueRef second_register)
{
	if (type < AST_OPERATION_EQUAL || type > AST_OPERATION_GREATER_EQUAL)
	{
		fatal("bad ast type\n");
		exit_program();
		
		return NULL;
	}
	
	LLVMIntPredicate predicate = 0;
	switch (type)
	{
	case AST_OPERATION_EQUAL:
		predicate = LLVMIntEQ;
		break;
	case AST_OPERATION_NOT_EQUAL:
		predicate = LLVMIntNE;
		break;
	case AST_OPERATION_LESS_THAN:
		predicate = LLVMIntSLT;
		break;
	case AST_OPERATION_GREATER_THAN:
		predicate = LLVMIntSGT;
		break;
	case AST_OPERATION_LESS_EQUAL:
		predicate = LLVMIntSLE;
		break;
	case AST_OPERATION_GREATER_EQUAL:
		predicate = LLVMIntSGT;
		break;
	default:
		break;
	}
	
	LLVMValueRef first_value = load_register(first_register);
	LLVMValueRef second_value = load_register(second_register);
	LLVMValueRef compare_register = LLVMBuildICmp(builder, predicate, first_value, second_value, "");
	LLVMValueRef value = LLVMBuildZExt(builder, compare_register, int_32_type, "");
	LLVMTypeRef value_type = LLVMTypeOf(value);
	
	LLVMValueRef value_register = store_register(value, value_type);
	return value_register;
}

static void generate_compare_and_jump(
	int type,
	LLVMValueRef first_register,
	LLVMValueRef second_register,
	LLVMBasicBlockRef first_label,
	LLVMBasicBlockRef second_label)
{
	if (type < AST_OPERATION_EQUAL || type > AST_OPERATION_GREATER_EQUAL)
	{
		fatal("bad ast type\n");
		exit_program();
		
		return;
	}
	
	LLVMIntPredicate predicate = 0;
	switch (type)
	{
	case AST_OPERATION_EQUAL:
		predicate = LLVMIntEQ;
		break;
	case AST_OPERATION_NOT_EQUAL:
		predicate = LLVMIntNE;
		break;
	case AST_OPERATION_LESS_THAN:
		predicate = LLVMIntSLT;
		break;
	case AST_OPERATION_GREATER_THAN:
		predicate = LLVMIntSGT;
		break;
	case AST_OPERATION_LESS_EQUAL:
		predicate = LLVMIntSLE;
		break;
	case AST_OPERATION_GREATER_EQUAL:
		predicate = LLVMIntSGT;
		break;
	default:
		break;
	}
	
	LLVMValueRef first_value = load_register(first_register);
	LLVMTypeRef first_type = LLVMTypeOf(first_value);
	
	LLVMValueRef second_value = load_register(second_register);
	LLVMTypeRef second_type = LLVMTypeOf(second_value);
	
	LLVMValueRef cast_second_value = second_value;
	if (first_type == int_32_type && second_type != int_32_type)
	{
		cast_second_value = LLVMBuildZExtOrBitCast(builder, second_value, int_32_type, "");
	}
	
	LLVMValueRef cast_first_value = first_value;
	if (second_type == int_32_type && first_type != int_32_type)
	{
		cast_first_value = LLVMBuildZExtOrBitCast(builder, first_value, int_32_type, "");
	}
	
	LLVMValueRef compare_register = LLVMBuildICmp(builder, predicate, cast_first_value, cast_second_value, "");
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

static void generate_pre_function(const char* name)
{
	LLVMTypeRef function_type = LLVMFunctionType(int_32_type, NULL, 0, 0);
	current_function = LLVMAddFunction(module, name, function_type);
	
	LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, current_function, "entry");
	LLVMPositionBuilderAtEnd(builder, entry);
	
	if (!strcmp(name, "main"))
	{
		printf_format = LLVMBuildGlobalString(builder, "%i\n", ".str");
	}
}

static void generate_post_function()
{
	LLVMBuildRet(builder, LLVMConstInt(int_32_type, 0, 0));
}

void add_global_variable(int identifier)
{
	struct symbol* symbol = get_symbol(identifier);
	LLVMTypeRef type = symbol->primitive_type == PRIMITIVE_TYPE_CHAR ? int_8_type :  int_32_type;
	LLVMValueRef global = LLVMAddGlobal(module, type, symbol->name);
	LLVMSetInitializer(global, LLVMConstInt(type, 0, 0));
}

void generate_pre_code(void)
{
	LLVMTypeRef printf_function_args_type[] = { int_8_type_pointer };
	LLVMTypeRef printf_function_type = LLVMFunctionType(int_32_type, printf_function_args_type, 0, 1);
	printf_function = LLVMAddFunction(module, "printf", printf_function_type);
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
	switch (ast->operation)
	{
	case AST_OPERATION_IF:
		generate_if(ast);
		return NULL;
	case AST_OPERATION_WHILE:
		generate_while(ast);
		return NULL;
	case AST_OPERATION_GLUE:
		generate_ast(ast->left, NULL, NULL, ast->operation);
		generate_ast(ast->right, NULL, NULL, ast->operation);
		return NULL;
	case AST_OPERATION_FUNCTION:
		generate_pre_function(get_symbol(ast->value.identifier)->name);
		generate_ast(ast->left, NULL, NULL, ast->operation);
		generate_post_function();
		return NULL;
	default:
		break;
	}
	
	LLVMValueRef left_register = NULL;
	if (ast->left)
	{
		left_register = generate_ast(ast->left, NULL, NULL, ast->operation);
	}
	
	LLVMValueRef right_register = NULL;
	if (ast->right)
	{
		right_register = generate_ast(ast->right, left_register, NULL, ast->operation);
	}
	
	switch (ast->operation)
	{
	case AST_OPERATION_ADD:
		return generate_add(left_register, right_register);
	case AST_OPERATION_SUBTRACT:
		return generate_subtract(left_register, right_register);
	case AST_OPERATION_MULTIPLY:
		return generate_multiplication(left_register, right_register);
	case AST_OPERATION_DIVIDE:
		return generate_division(left_register, right_register);
	case AST_OPERATION_EQUAL:
	case AST_OPERATION_NOT_EQUAL:
	case AST_OPERATION_LESS_THAN:
	case AST_OPERATION_GREATER_THAN:
	case AST_OPERATION_LESS_EQUAL:
	case AST_OPERATION_GREATER_EQUAL:
		if (parent_type == AST_OPERATION_IF || parent_type == AST_OPERATION_WHILE)
		{
			generate_compare_and_jump(ast->operation, left_register, right_register, labels[0], labels[1]);
			return NULL;
		}
		
		return generate_compare_and_set(ast->operation, left_register, right_register);
	case AST_OPERATION_INT_LITERAL:
		return store_value(ast->value.int_value, (ast->type == PRIMITIVE_TYPE_CHAR) ?  int_8_type : int_32_type);
	case AST_OPERATION_L_VALUE:
		return store_global_register(reg, get_symbol(ast->value.identifier)->name);
	case AST_OPERATION_IDENTIFIER:
		return load_global_register(get_symbol(ast->value.identifier)->name);
	case AST_OPERATION_ASSIGN:
		return right_register;
	case AST_OPERATION_PRINT:
		generate_print_register(left_register);
		return NULL;
	case AST_OPERATION_WIDEN:
		return left_register;
	default:
		break;
	}
	
	fatal("unknown ast operation\n");
	exit_program();
	
	return NULL;
}

/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_GENERATOR_H_
#define HYPERLANG_GENERATOR_H_

#include "ast.h"

#include <llvm-c/Types.h>

void init_generator(const char* file_name);
void free_generator(void);

void add_global_variable(int identifier);

void generate_pre_code(void);

LLVMValueRef generate_ast(
	struct ast* ast,
	LLVMValueRef reg,
	LLVMBasicBlockRef* labels,
	int parent_type);

void generate_code(void);

#endif // HYPERLANG_GENERATOR_H_

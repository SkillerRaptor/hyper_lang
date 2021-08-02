/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/BuildOptions.hpp"

#include <llvm-c/Core.h>
#include <llvm-c/TargetMachine.h>

#include <string>

namespace HyperCompiler
{
	class AstNode;

	class LLVMGenerator
		{
		public:
			void initialize(const BuildOptions& build_options, const std::string& file_name);
			void shutdown();

			void generate_object(AstNode* ast_node);

		private:
			void generate_pre_code();
			void generate_post_code();

			void generate_target_machine();

		private:
			BuildOptions m_build_options{};
			std::string m_file_name;

			LLVMContextRef m_context{ nullptr };
			LLVMModuleRef m_module{ nullptr };
			LLVMBuilderRef m_builder{ nullptr };

			LLVMTypeRef m_int_8_type{ nullptr };
			LLVMTypeRef m_int_8_type_pointer{ nullptr };
			LLVMTypeRef m_int_32_type{ nullptr };
			LLVMTypeRef m_int_32_type_pointer{ nullptr };

			LLVMTargetMachineRef m_target_machine{ nullptr };

			LLVMValueRef m_printf_function{ nullptr };
			LLVMValueRef m_printf_format{ nullptr };

			LLVMValueRef m_main_function{ nullptr };
		};
} // namespace HyperCompiler

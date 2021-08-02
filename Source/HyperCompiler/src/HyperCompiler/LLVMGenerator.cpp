/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/LLVMGenerator.hpp"

#include "HyperCompiler/Utils/Utilities.hpp"
#include "HyperCompiler/Ast/AstNode.hpp"

namespace HyperCompiler
{
	void LLVMGenerator::initialize(const BuildOptions& build_options, const std::string& file_name)
	{
		m_build_options = build_options;
		m_file_name = file_name;

		m_context = LLVMContextCreate();
		m_module = LLVMModuleCreateWithNameInContext(m_file_name.c_str(), m_context);
		m_builder = LLVMCreateBuilderInContext(m_context);
		m_int_8_type = LLVMInt8TypeInContext(m_context);
		m_int_8_type_pointer = LLVMPointerType(m_int_8_type, 0);
		m_int_32_type = LLVMInt32TypeInContext(m_context);
		m_int_32_type_pointer = LLVMPointerType(m_int_32_type, 0);

		generate_target_machine();
	}

	void LLVMGenerator::shutdown()
	{
		LLVMDisposeTargetMachine(m_target_machine);

		LLVMDisposeBuilder(m_builder);
		LLVMDisposeModule(m_module);
		LLVMContextDispose(m_context);
	}

	void LLVMGenerator::generate_object(AstNode* ast_node)
	{
		generate_pre_code();
		ast_node->generate(*this);
		generate_post_code();

		LLVMPrintModuleToFile(
			m_module,
			(m_file_name + ".ll").c_str(),
			nullptr);
		
		char* object_file_name = Utils::duplicate_string((m_file_name + ".o").c_str());
		LLVMTargetMachineEmitToFile(
			m_target_machine,
			m_module,
			object_file_name,
			LLVMObjectFile,
			nullptr);

		delete[] object_file_name;
	}

	void LLVMGenerator::generate_pre_code()
	{
		LLVMTypeRef printf_function_args_type[] = { m_int_8_type_pointer };
		LLVMTypeRef printf_function_type = LLVMFunctionType(m_int_32_type, printf_function_args_type, 0, 1);
		m_printf_function = LLVMAddFunction(m_module, "printf", printf_function_type);

		LLVMTypeRef main_function_type = LLVMFunctionType(m_int_32_type, nullptr, 0, 0);
		m_main_function = LLVMAddFunction(m_module, "main", main_function_type);

		LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(m_context, m_main_function, "entry");
		LLVMPositionBuilderAtEnd(m_builder, entry);

		m_printf_format = LLVMBuildGlobalString(m_builder, "%i\n", ".str");
	}

	void LLVMGenerator::generate_post_code()
	{
		LLVMBuildRet(m_builder, LLVMConstInt(m_int_32_type, 0, 0));
	}

	void LLVMGenerator::generate_target_machine()
	{
		const std::string arch = [this]()
		{
			switch (m_build_options.arch_target)
			{
			case ArchTarget::x86:
				return "i386";
			case ArchTarget::x86_64:
				return "x86_64";
			default:
				return "undefined";
			}
		}();

		const std::string os = [this]()
		{
			switch (m_build_options.os_target)
			{
			case OsTarget::Linux:
				return "linux";
			case OsTarget::Windows:
				return "windows";
			default:
				return "undefined";
			}
		}();

		const LLVMCodeGenOptLevel optimization_level = [this]()
		{
			switch (m_build_options.optimization_level)
			{
			case OptimizationLevel::None:
				return LLVMCodeGenLevelNone;
			case OptimizationLevel::Less:
				return LLVMCodeGenLevelLess;
			case OptimizationLevel::Default:
				return LLVMCodeGenLevelDefault;
			case OptimizationLevel::Aggressive:
				return LLVMCodeGenLevelAggressive;
			default:
				return LLVMCodeGenLevelNone;
			}
		}();

		std::string triplet = arch + "-unknown-" + os + "-unknown";
		
		LLVMInitializeAllTargetInfos();
		LLVMInitializeAllTargets();
		LLVMInitializeAllTargetMCs();

		LLVMInitializeAllAsmParsers();
		LLVMInitializeAllAsmPrinters();
		
		LLVMTargetRef target;
		LLVMGetTargetFromTriple(triplet.c_str(), &target, nullptr);
		
		m_target_machine = LLVMCreateTargetMachine(
			target,
			triplet.c_str(),
			"\0",
			"\0",
			optimization_level,
			LLVMRelocDefault,
			LLVMCodeModelDefault);
	}
} // namespace HyperCompiler

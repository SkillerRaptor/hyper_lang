/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Ast/Expressions.hpp"

namespace HyperCompiler
{
	class Literal : public Expression
	{
	public:
		virtual ~Literal() = default;

		virtual std::string class_name() const override;
	};

	class BoolLiteral final : public Literal
	{
	public:
		explicit BoolLiteral(bool value);
		
		virtual void generate(LLVMGenerator& llvm_generator) const override;
		virtual void dump(unsigned int indent) const override;

		virtual std::string class_name() const override;

	private:
		bool m_value{ false };
	};

	class NumericLiteral final : public Literal
	{
	public:
		explicit NumericLiteral(int8_t value);
		explicit NumericLiteral(int16_t value);
		explicit NumericLiteral(int32_t value);
		explicit NumericLiteral(int64_t value);
		explicit NumericLiteral(uint8_t value);
		explicit NumericLiteral(uint16_t value);
		explicit NumericLiteral(uint32_t value);
		explicit NumericLiteral(uint64_t value);

		virtual void generate(LLVMGenerator& llvm_generator) const override;
		virtual void dump(unsigned int indent) const override;

		virtual std::string class_name() const override;

	private:
		Value m_value{};
	};
} // namespace HyperCompiler

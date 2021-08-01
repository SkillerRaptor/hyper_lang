/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "HyperCompiler/Ast/AstNode.hpp"

namespace HyperCompiler
{
	class Expression : public AstNode
	{
	public:
		virtual ~Expression() override = default;

		virtual std::string class_name() const override;
	};

	class BinaryExpression final : public Expression
	{
	public:
		enum class Operation : uint16_t
		{
			Addition,
			Subtraction,
			Multiplication,
			Division,
			Modulo,
			LessThan,
			GreaterThan,
			BitwiseAnd,
			BitwiseOr,
			BitwiseXor
		};

	public:
		BinaryExpression(Operation operation, Expression* left, Expression* right);
		virtual ~BinaryExpression() override;

		virtual Value execute() const override;
		virtual void dump(unsigned int indent) const override;

		virtual std::string class_name() const override;

	private:
		Operation m_operation{};
		Expression* m_left{ nullptr };
		Expression* m_right{ nullptr };
	};
	
	std::ostream& operator<<(std::ostream& ostream, const BinaryExpression::Operation& operation);
} // namespace HyperCompiler

/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

#include "Hyper/Generators/Generator.hpp"

#include <iostream>

namespace Hyper
{
	BinaryExpression::BinaryExpression(
		BinaryExpression::Operation operation,
		std::unique_ptr<Expression> left,
		std::unique_ptr<Expression> right)
		: m_operation(operation)
		, m_left(std::move(left))
		, m_right(std::move(right))
	{
	}

	void BinaryExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void BinaryExpression::dump(size_t indent) const
	{
		AstNode::dump(indent);

		std::cout << "operation = " << m_operation;
		std::cout << '\n';

		m_left->dump(indent + 1);
		m_right->dump(indent + 1);
	}

	const char *BinaryExpression::class_name() const noexcept
	{
		return "BinaryExpression";
	}

	BinaryExpression::Operation BinaryExpression::operation() const noexcept
	{
		return m_operation;
	}

	const std::unique_ptr<Expression> &BinaryExpression::left() const
	{
		return m_left;
	}

	const std::unique_ptr<Expression> &BinaryExpression::right() const
	{
		return m_right;
	}

	std::ostream &operator<<(
		std::ostream &ostream,
		const BinaryExpression::Operation &operation)
	{
		switch (operation)
		{
		case BinaryExpression::Operation::Addition:
			ostream << "Addition";
			break;
		case BinaryExpression::Operation::Subtraction:
			ostream << "Subtraction";
			break;
		case BinaryExpression::Operation::Multiplication:
			ostream << "Multiplication";
			break;
		case BinaryExpression::Operation::Division:
			ostream << "Division";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper

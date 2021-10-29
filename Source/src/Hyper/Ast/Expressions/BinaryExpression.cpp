/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

#include "Hyper/Generator.hpp"
#include "Hyper/Operators.hpp"

#include <iostream>

namespace Hyper
{
	BinaryExpression::BinaryExpression(
		BinaryExpression::Operation operation,
		Expression *left,
		Expression *right)
		: m_operation(operation)
		, m_left(left)
		, m_right(right)
	{
	}

	BinaryExpression::~BinaryExpression()
	{
		delete m_left;
		delete m_right;
	}

	void BinaryExpression::generate(Generator &generator) const
	{
		m_left->generate(generator);

		switch (m_operation)
		{
		case Operation::Addition:
			generator.generate_operator(Operator::Plus);
			break;
		case Operation::Subtraction:
			generator.generate_operator(Operator::Minus);
			break;
		case Operation::Multiplication:
			generator.generate_operator(Operator::Star);
			break;
		case Operation::Division:
			generator.generate_operator(Operator::Slash);
			break;
		default:
			// TODO(SkillerRaptor): Error handling
			std::abort();
		}

		m_right->generate(generator);
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

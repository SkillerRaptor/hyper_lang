/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

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

	void BinaryExpression::dump(size_t indent) const
	{
		AstNode::dump(indent);
		
		std::cout << "operation = " << m_operation;
		
		std::cout << '\n';
		
		++indent;
		
		m_left->dump(indent);
		m_right->dump(indent);
	}

	const char *BinaryExpression::name() const noexcept
	{
		return "BinaryExpression";
	}
	
	std::ostream &operator<<(
		std::ostream &ostream,
		const BinaryExpression::Operation &operation)
	{
		switch (operation)
		{
		case BinaryExpression::Operation::None:
			break;
		case BinaryExpression::Operation::Addition:
			std::cout << "Addition";
			break;
		case BinaryExpression::Operation::Subtraction:
			std::cout << "Subtraction";
			break;
		case BinaryExpression::Operation::Multiplication:
			std::cout << "Multiplication";
			break;
		case BinaryExpression::Operation::Division:
			std::cout << "Division";
			break;
		}
		return ostream;
	}
} // namespace Hyper

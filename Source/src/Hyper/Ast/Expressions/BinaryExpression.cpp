/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

namespace Hyper
{
	BinaryExpression::BinaryExpression(
		BinaryExpression::Operation operation,
		ExpressionPtr left,
		ExpressionPtr right)
		: m_operation(operation)
		, m_left(std::move(left))
		, m_right(std::move(right))
	{
	}

	void BinaryExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void BinaryExpression::dump(const std::string &prefix, bool last) const
	{
		AstNode::print_prefix(prefix, last);

		Logger::raw("(operation={})\n", m_operation);

		AstNode::print_next_node(*m_left, prefix, last, false);
		AstNode::print_next_node(*m_right, prefix, last, true);
	}

	AstNode::Category BinaryExpression::class_category() const noexcept
	{
		return AstNode::Category::BinaryExpression;
	}

	std::string_view BinaryExpression::class_name() const noexcept
	{
		return "BinaryExpression";
	}

	BinaryExpression::Operation BinaryExpression::operation() const noexcept
	{
		return m_operation;
	}

	const ExpressionPtr &BinaryExpression::left() const
	{
		return m_left;
	}

	const ExpressionPtr &BinaryExpression::right() const
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
		case BinaryExpression::Operation::Equal:
			ostream << "Equal";
			break;
		case BinaryExpression::Operation::NotEqual:
			ostream << "NotEqual";
			break;
		case BinaryExpression::Operation::LessThan:
			ostream << "LessThan";
			break;
		case BinaryExpression::Operation::GreaterThan:
			ostream << "GreaterThan";
			break;
		case BinaryExpression::Operation::LessEqual:
			ostream << "LessEqual";
			break;
		case BinaryExpression::Operation::GreaterEqual:
			ostream << "GreaterEqual";
			break;
		default:
			break;
		}

		return ostream;
	}
} // namespace Hyper

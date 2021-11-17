/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

#include <cassert>

namespace Hyper
{
	BinaryExpression::BinaryExpression(BinaryExpression::CreateInfo create_info)
		: m_operation(create_info.operation)
		, m_left(std::move(create_info.left))
		, m_right(std::move(create_info.right))
	{
	}

	void BinaryExpression::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void BinaryExpression::dump(const std::string &prefix, bool is_self_last)
		const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);

		AstNode::dump_next_node(*m_left, prefix, is_self_last, false);
		AstNode::dump_next_node(*m_right, prefix, is_self_last, true);
	}

	AstNode::Category BinaryExpression::class_category() const noexcept
	{
		return AstNode::Category::BinaryExpression;
	}

	std::string_view BinaryExpression::class_name() const noexcept
	{
		return "BinaryExpression";
	}

	std::string BinaryExpression::class_description() const
	{
		const std::string operation =
			AstFormatter::format_member("operation", m_operation);

		return Formatter::format("({})", operation);
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
		assert(operation != BinaryExpression::Operation::None);

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
			HYPER_UNREACHABLE();
			break;
		}

		return ostream;
	}
} // namespace Hyper

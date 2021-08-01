/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Ast/Expressions.hpp"

#include "HyperCompiler/Logger.hpp"
#include "HyperCompiler/Utils/Assertion.hpp"

namespace HyperCompiler
{
	std::string Expression::class_name() const
	{
		return "Expression";
	}

	BinaryExpression::BinaryExpression(BinaryExpression::Operation operation, Expression* left, Expression* right)
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

	Value BinaryExpression::execute() const
	{
		const Value left_result = m_left->execute();
		if (left_result.is_undefined())
		{
			return {};
		}

		const Value right_result = m_right->execute();
		if (right_result.is_undefined())
		{
			return {};
		}

		switch (m_operation)
		{
		case Operation::Addition:
			return Value::add(left_result, right_result);
		case Operation::Subtraction:
			return Value::subtract(left_result, right_result);
		case Operation::Multiplication:
			return Value::multiply(left_result, right_result);
		case Operation::Division:
			return Value::divide(left_result, right_result);
		case Operation::Modulo:
		case Operation::LessThan:
		case Operation::GreaterThan:
		case Operation::BitwiseAnd:
		case Operation::BitwiseOr:
		case Operation::BitwiseXor:
			return {};
		default:
			break;
		}

		ASSERT_NOT_REACHED();
	}

	std::string BinaryExpression::class_name() const
	{
		return "BinaryExpression";
	}
	
	void BinaryExpression::dump(unsigned int indent) const
	{
		AstNode::dump(indent++);
		Logger::info_indent(indent, "Operation: {}\n", m_operation);
		
		m_left->dump(indent);
		m_right->dump(indent);
	}
	
	std::ostream& operator<<(std::ostream& ostream, const BinaryExpression::Operation& operation)
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
		case BinaryExpression::Operation::Modulo:
			ostream << "Modulo";
			break;
		case BinaryExpression::Operation::LessThan:
			ostream << "LessThan";
			break;
		case BinaryExpression::Operation::GreaterThan:
			ostream << "GreaterThan";
			break;
		case BinaryExpression::Operation::BitwiseAnd:
			ostream << "BitwiseAnd";
			break;
		case BinaryExpression::Operation::BitwiseOr:
			ostream << "BitwiseOr";
			break;
		case BinaryExpression::Operation::BitwiseXor:
			ostream << "BitwiseXor";
			break;
		}
		
		return ostream;
	}
} // namespace HyperCompiler

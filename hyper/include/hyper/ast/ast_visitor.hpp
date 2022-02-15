/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast.hpp"
#include "hyper/utilities.hpp"

#include <type_traits>

namespace hyper
{
	template <typename Derived>
	class AstVisitor
	{
	public:
		virtual ~AstVisitor() = default;

		void traverse(const AstNode *ast_node)
		{
			if (
				ast_node->class_category() !=
				AstNode::Category::TranslationUnitDeclaration)
			{
				return;
			}

			const Declaration *declaration =
				static_cast<const Declaration *>(ast_node);
			traverse_declaration(declaration);
		}

	protected:
		virtual void traverse_declaration(const Declaration *declaration)
		{
			switch (declaration->class_category())
			{
			case AstNode::Category::ExportDeclaration:
				traverse_export_declaration(declaration);
				break;
			case AstNode::Category::ExternDeclaration:
				traverse_extern_declaration(declaration);
				break;
			case AstNode::Category::FunctionDeclaration:
				traverse_function_declaration(declaration);
				break;
			case AstNode::Category::ImportDeclaration:
				traverse_import_declaration(declaration);
				break;
			case AstNode::Category::ParameterDeclaration:
				traverse_parameter_declaration(declaration);
				break;
			case AstNode::Category::TranslationUnitDeclaration:
				traverse_translation_unit_declaration(declaration);
				break;
			case AstNode::Category::VariableDeclaration:
				traverse_variable_declaration(declaration);
				break;
			default:
				std::abort();
			}
		}

		virtual void traverse_expression(const Expression *expression)
		{
			if (expression->class_kind() == AstNode::Kind::Literal)
			{
				const Literal *literal = static_cast<const Literal *>(expression);
				traverse_literal(literal);
				return;
			}

			switch (expression->class_category())
			{
			case AstNode::Category::BinaryExpression:
				traverse_binary_expression(expression);
				break;
			case AstNode::Category::CallExpression:
				traverse_call_expression(expression);
				break;
			case AstNode::Category::CastExpression:
				traverse_cast_expression(expression);
				break;
			case AstNode::Category::ConditionalExpression:
				traverse_conditional_expression(expression);
				break;
			case AstNode::Category::IdentifierExpression:
				traverse_identifier_expression(expression);
				break;
			case AstNode::Category::UnaryExpression:
				traverse_unary_expression(expression);
				break;
			default:
				std::abort();
			}
		}

		virtual void traverse_literal(const Literal *literal)
		{
			switch (literal->class_category())
			{
			case AstNode::Category::BoolLiteral:
				traverse_bool_literal(literal);
				break;
			case AstNode::Category::FloatingLiteral:
				traverse_floating_literal(literal);
				break;
			case AstNode::Category::IntegerLiteral:
				traverse_integer_literal(literal);
				break;
			case AstNode::Category::StringLiteral:
				traverse_string_literal(literal);
				break;
			default:
				std::abort();
			}
		}

		virtual void traverse_statement(const Statement *statement)
		{
			if (statement->class_kind() == AstNode::Kind::Declaration)
			{
				const Declaration *declaration =
					static_cast<const Declaration *>(statement);
				traverse_declaration(declaration);
				return;
			}

			switch (statement->class_category())
			{
			case AstNode::Category::AssignStatement:
				traverse_assign_statement(statement);
				break;
			case AstNode::Category::CompoundAssignStatement:
				traverse_compound_assign_statement(statement);
				break;
			case AstNode::Category::CompoundStatement:
				traverse_compound_statement(statement);
				break;
			case AstNode::Category::ExpressionStatement:
				traverse_expression_statement(statement);
				break;
			case AstNode::Category::IfStatement:
				traverse_if_statement(statement);
				break;
			case AstNode::Category::PrintStatement:
				traverse_print_statement(statement);
				break;
			case AstNode::Category::ReturnStatement:
				traverse_return_statement(statement);
				break;
			case AstNode::Category::WhileStatement:
				traverse_while_statement(statement);
				break;
			default:
				std::abort();
			}
		}

	private:
		Derived &get_derived()
		{
			return *static_cast<Derived *>(this);
		}

#define VISIT_NODE(type, function)                                       \
	Derived &derived = get_derived();                                      \
	const type *function = static_cast<const type *>(node);                \
	do                                                                     \
	{                                                                      \
		if constexpr (requires {                                             \
										{                                                    \
											std::declval<Derived>().visit_##function(function) \
											} -> ConvertibleTo<bool>;                          \
									})                                                     \
		{                                                                    \
			if (!derived.visit_##function(function))                           \
			{                                                                  \
				return;                                                          \
			}                                                                  \
		}                                                                    \
	} while (false)

		void traverse_export_declaration(const Declaration *node)
		{
			VISIT_NODE(ExportDeclaration, export_declaration);

			derived.traverse_statement(export_declaration->statement());
		}

		void traverse_extern_declaration(const Declaration *node)
		{
			VISIT_NODE(ExternDeclaration, extern_declaration);

			derived.traverse_statement(extern_declaration->statement());
		}

		void traverse_function_declaration(const Declaration *node)
		{
			VISIT_NODE(FunctionDeclaration, function_declaration);

			for (const Declaration *argument : function_declaration->arguments())
			{
				derived.traverse_declaration(argument);
			}

			if (function_declaration->body())
			{
				derived.traverse_statement(function_declaration->body());
			}
		}

		void traverse_import_declaration(const Declaration *node)
		{
			VISIT_NODE(ImportDeclaration, import_declaration);
		}

		void traverse_parameter_declaration(const Declaration *node)
		{
			VISIT_NODE(ParameterDeclaration, parameter_declaration);
		}

		void traverse_translation_unit_declaration(const Declaration *node)
		{
			VISIT_NODE(TranslationUnitDeclaration, translation_unit_declaration);

			for (const Declaration *declaration :
					 translation_unit_declaration->declarations())
			{
				derived.traverse_declaration(declaration);
			}
		}

		void traverse_variable_declaration(const Declaration *node)
		{
			VISIT_NODE(VariableDeclaration, variable_declaration);

			if (variable_declaration->expression())
			{
				derived.traverse_expression(variable_declaration->expression());
			}
		}

		void traverse_binary_expression(const Expression *node)
		{
			VISIT_NODE(BinaryExpression, binary_expression);

			derived.traverse_expression(binary_expression->left());
			derived.traverse_expression(binary_expression->right());
		}

		void traverse_call_expression(const Expression *node)
		{
			VISIT_NODE(CallExpression, call_expression);

			for (const Expression *argument : call_expression->arguments())
			{
				derived.traverse_expression(argument);
			}
		}

		void traverse_cast_expression(const Expression *node)
		{
			VISIT_NODE(CastExpression, cast_expression);

			derived.traverse_expression(cast_expression->expression());
		}

		void traverse_conditional_expression(const Expression *node)
		{
			VISIT_NODE(ConditionalExpression, conditional_expression);

			derived.traverse_expression(conditional_expression->condition());
			derived.traverse_expression(conditional_expression->true_expression());

			if (conditional_expression->false_expression())
			{
				derived.traverse_expression(conditional_expression->false_expression());
			}
		}

		void traverse_identifier_expression(const Expression *node)
		{
			VISIT_NODE(IdentifierExpression, identifier_expression);
		}

		void traverse_unary_expression(const Expression *node)
		{
			VISIT_NODE(UnaryExpression, unary_expression);

			derived.traverse_expression(unary_expression->expression());
		}

		void traverse_bool_literal(const Literal *node)
		{
			VISIT_NODE(BoolLiteral, bool_literal);
		}

		void traverse_floating_literal(const Literal *node)
		{
			VISIT_NODE(FloatingLiteral, floating_literal);
		}

		void traverse_integer_literal(const Literal *node)
		{
			VISIT_NODE(IntegerLiteral, integer_literal);
		}

		void traverse_string_literal(const Literal *node)
		{
			VISIT_NODE(StringLiteral, string_literal);
		}

		void traverse_assign_statement(const Statement *node)
		{
			VISIT_NODE(AssignStatement, assign_statement);

			derived.traverse_expression(assign_statement->expression());
		}

		void traverse_compound_assign_statement(const Statement *node)
		{
			VISIT_NODE(CompoundAssignStatement, compound_assign_statement);

			derived.traverse_expression(compound_assign_statement->expression());
		}

		void traverse_compound_statement(const Statement *node)
		{
			VISIT_NODE(CompoundStatement, compound_statement);

			for (const Statement *statement : compound_statement->statements())
			{
				derived.traverse_statement(statement);
			}
		}

		void traverse_expression_statement(const Statement *node)
		{
			VISIT_NODE(ExpressionStatement, expression_statement);

			derived.traverse_expression(expression_statement->expression());
		}

		void traverse_if_statement(const Statement *node)
		{
			VISIT_NODE(IfStatement, if_statement);

			derived.traverse_expression(if_statement->condition());
			derived.traverse_statement(if_statement->true_body());

			if (if_statement->false_body())
			{
				derived.traverse_statement(if_statement->false_body());
			}
		}

		void traverse_print_statement(const Statement *node)
		{
			VISIT_NODE(PrintStatement, print_statement);

			derived.traverse_expression(print_statement->expression());
		}

		void traverse_return_statement(const Statement *node)
		{
			VISIT_NODE(ReturnStatement, return_statement);

			if (return_statement->expression())
			{
				derived.traverse_expression(return_statement->expression());
			}
		}

		void traverse_while_statement(const Statement *node)
		{
			VISIT_NODE(WhileStatement, while_statement);

			derived.traverse_expression(while_statement->condition());
			derived.traverse_statement(while_statement->body());
		}
	};
} // namespace hyper

/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/backends/c/c_generator.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>

namespace hyper
{
	CGenerator::CGenerator(std::string output_file)
		: m_output_file(std::move(output_file))
	{
	}

	bool CGenerator::visit_export_declaration(
		const PublicDeclaration *export_declaration)
	{
		const Statement *statement = export_declaration->statement();
		if (statement->class_category() != AstNode::Category::FunctionDeclaration)
		{
			return true;
		}

		const FunctionDeclaration *function_declaration =
			static_cast<const FunctionDeclaration *>(statement);
		const std::string type = map_data_type(function_declaration->return_type());
		m_header << '\n'
						 << type << " " << function_declaration->identifier().value
						 << "();\n";

		return true;
	}

	bool CGenerator::visit_extern_declaration(
		const ExternDeclaration *extern_declaration)
	{
		const Statement *statement = extern_declaration->statement();
		if (statement->class_category() != AstNode::Category::FunctionDeclaration)
		{
			return true;
		}

		const FunctionDeclaration *function_declaration =
			static_cast<const FunctionDeclaration *>(statement);
		const std::string type = map_data_type(function_declaration->return_type());
		m_source << "\nextern " << type << " "
						 << function_declaration->identifier().value << "();\n";

		return false;
	}

	bool CGenerator::visit_function_declaration(
		const FunctionDeclaration *function_declaration)
	{
		const std::string type = map_data_type(function_declaration->return_type());
		m_source << '\n'
						 << type << " " << function_declaration->identifier().value << '(';

		for (const Declaration *argument : function_declaration->arguments())
		{
			traverse_declaration(argument);
		}

		m_source << ")\n";

		start_scope();
		if (function_declaration->body())
		{
			traverse_statement(function_declaration->body());
		}
		end_scope();

		return false;
	}

	bool CGenerator::visit_import_declaration(
		const ImportDeclaration *import_declaration)
	{
		m_header << "#include <" << import_declaration->file_name() << ".h>\n";

		return true;
	}

	bool CGenerator::visit_parameter_declaration(
		const ParameterDeclaration *parameter_declaration)
	{
		const std::string type = map_data_type(parameter_declaration->type());

		if (
			parameter_declaration->mutable_state() ==
				ParameterDeclaration::MutableState::No &&
			parameter_declaration->type().kind() != DataType::Kind::String)
		{
			m_source << "const ";
		}

		m_source << type << " " << parameter_declaration->identifier().value;

		return true;
	}

	bool CGenerator::visit_translation_unit_declaration(
		const TranslationUnitDeclaration *translation_unit_declaration)
	{
		const std::filesystem::path path = m_output_file;
		const std::string file_name = path.filename().string();

		m_source << "/*\n";
		m_source << " * Copyright (c) 2020-present, SkillerRaptor "
								"<skillerraptor@protonmail.com>\n";
		m_source << " *\n";
		m_source << " * SPDX-License-Identifier: MIT\n";
		m_source << " */\n";
		m_source << '\n';
		m_source << "#include \"" << file_name << ".h\"\n";

		m_header << "/*\n";
		m_header << " * Copyright (c) 2020-present, SkillerRaptor "
								"<skillerraptor@protonmail.com>\n";
		m_header << " *\n";
		m_header << " * SPDX-License-Identifier: MIT\n";
		m_header << " */\n";
		m_header << '\n';

		std::string include_guard = "__" + file_name + "_H__";
		std::transform(
			include_guard.begin(),
			include_guard.end(),
			include_guard.begin(),
			[](unsigned char character)
			{
				return static_cast<char>(std::toupper(character));
			});
		std::replace(include_guard.begin(), include_guard.end(), '.', '_');

		m_header << "#ifndef " << include_guard << '\n';
		m_header << "#define " << include_guard << '\n';
		m_header << '\n';
		m_header << "#include <stdbool.h>\n";
		m_header << "#include <stdint.h>\n";
		m_header << "#include <stdio.h>\n";

		for (const Declaration *declaration :
				 translation_unit_declaration->declarations())
		{
			traverse_declaration(declaration);
		}

		m_header << '\n';
		m_header << "#endif\n";

		std::ofstream source(m_output_file + ".c");
		std::ofstream header(m_output_file + ".h");

		source << m_source.str();
		header << m_header.str();

		source.close();
		header.close();

		return false;
	}

	bool CGenerator::visit_variable_declaration(
		const VariableDeclaration *variable_declaration)
	{
		const std::string type = map_data_type(variable_declaration->type());

		m_source << m_indention;

		if (
			variable_declaration->mutable_state() ==
				VariableDeclaration::MutableState::No &&
			variable_declaration->type().kind() != DataType::Kind::String)
		{
			m_source << "const ";
		}

		m_source << type << " " << variable_declaration->identifier().value;

		if (variable_declaration->expression())
		{
			m_source << " = ";
		}

		traverse_expression(variable_declaration->expression());

		m_source << ";\n";

		return false;
	}

	bool CGenerator::visit_binary_expression(
		const BinaryExpression *binary_expression)
	{
		traverse_expression(binary_expression->left());

		m_source << ' ';

		switch (binary_expression->operation().kind)
		{
		case BinaryExpression::Operation::Kind::Addition:
			m_source << "+";
			break;
		case BinaryExpression::Operation::Kind::Subtraction:
			m_source << "-";
			break;
		case BinaryExpression::Operation::Kind::Multiplication:
			m_source << "*";
			break;
		case BinaryExpression::Operation::Kind::Division:
			m_source << "/";
			break;
		case BinaryExpression::Operation::Kind::Modulo:
			m_source << "%";
			break;
		case BinaryExpression::Operation::Kind::BitwiseAnd:
			m_source << "&";
			break;
		case BinaryExpression::Operation::Kind::BitwiseOr:
			m_source << "|";
			break;
		case BinaryExpression::Operation::Kind::BitwiseXor:
			m_source << "^";
			break;
		case BinaryExpression::Operation::Kind::LeftShift:
			m_source << "<<";
			break;
		case BinaryExpression::Operation::Kind::RightShift:
			m_source << ">>";
			break;
		case BinaryExpression::Operation::Kind::LogicalAnd:
			m_source << "&&";
			break;
		case BinaryExpression::Operation::Kind::LogicalOr:
			m_source << "||";
			break;
		case BinaryExpression::Operation::Kind::Equal:
			m_source << "==";
			break;
		case BinaryExpression::Operation::Kind::NotEqual:
			m_source << "!=";
			break;
		case BinaryExpression::Operation::Kind::LessThan:
			m_source << "<";
			break;
		case BinaryExpression::Operation::Kind::GreaterThan:
			m_source << ">";
			break;
		case BinaryExpression::Operation::Kind::LessEqual:
			m_source << "<=";
			break;
		case BinaryExpression::Operation::Kind::GreaterEqual:
			m_source << ">=";
			break;
		default:
			std::abort();
		}

		m_source << ' ';

		traverse_expression(binary_expression->right());

		return false;
	}

	bool CGenerator::visit_call_expression(const CallExpression *call_expression)
	{
		m_source << call_expression->identifier().value << "(";

		for (const Expression *argument : call_expression->arguments())
		{
			traverse_expression(argument);

			if (argument != call_expression->arguments().back())
			{
				m_source << ", ";
			}
		}

		m_source << ")";

		return false;
	}

	bool CGenerator::visit_cast_expression(const CastExpression *cast_expression)
	{
		const std::string type = map_data_type(cast_expression->type());
		m_source << "((" << type << ") (";
		traverse_expression(cast_expression->expression());
		m_source << "))";

		return false;
	}

	bool CGenerator::visit_conditional_expression(
		const ConditionalExpression *conditional_expression)
	{
		traverse_expression(conditional_expression->condition());
		m_source << " ? ";
		traverse_expression(conditional_expression->true_expression());
		m_source << " : ";
		traverse_expression(conditional_expression->false_expression());

		return false;
	}

	bool CGenerator::visit_identifier_expression(
		const IdentifierExpression *identifier_expression)
	{
		m_source << identifier_expression->identifier().value;
		return true;
	}

	bool CGenerator::visit_unary_expression(
		const UnaryExpression *unary_expression)
	{
		switch (unary_expression->operation().kind)
		{
		case UnaryExpression::Operation::Kind::Invalid:
			std::abort();
		case UnaryExpression::Operation::Kind::Not:
			m_source << "!";
			break;
		case UnaryExpression::Operation::Kind::Negative:
			m_source << "-";
			break;
		case UnaryExpression::Operation::Kind::Inverse:
			m_source << "~";
			break;
		case UnaryExpression::Operation::Kind::PreIncrement:
			m_source << "++";
			break;
		case UnaryExpression::Operation::Kind::PreDecrement:
			m_source << "--";
			break;
		default:
			break;
		}

		traverse_expression(unary_expression->expression());

		switch (unary_expression->operation().kind)
		{
		case UnaryExpression::Operation::Kind::PostIncrement:
			m_source << "++";
			break;
		case UnaryExpression::Operation::Kind::PostDecrement:
			m_source << "--";
			break;
		default:
			break;
		}

		return false;
	}

	bool CGenerator::visit_bool_literal(const BoolLiteral *bool_literal)
	{
		m_source << (bool_literal->boolean() ? "true" : "false");
		return true;
	}

	bool CGenerator::visit_floating_literal(
		const FloatingLiteral *floating_literal)
	{
		m_source << floating_literal->floating();
		return true;
	}

	bool CGenerator::visit_integer_literal(const IntegerLiteral *integer_literal)
	{
		m_source << integer_literal->integer();
		return true;
	}

	bool CGenerator::visit_string_literal(const StringLiteral *string_literal)
	{
		m_source << string_literal->string();
		return true;
	}

	bool CGenerator::visit_assign_statement(
		const AssignStatement *assign_statement)
	{
		m_source << m_indention << assign_statement->identifier().value << " = ";
		traverse_expression(assign_statement->expression());
		m_source << ";\n";

		return false;
	}

	bool CGenerator::visit_compound_assign_statement(
		const CompoundAssignStatement *compound_assign_statement)
	{
		m_source << m_indention << compound_assign_statement->identifier().value
						 << " ";

		switch (compound_assign_statement->operation())
		{
		case CompoundAssignStatement::Operation::Addition:
			m_source << "+";
			break;
		case CompoundAssignStatement::Operation::Subtraction:
			m_source << "-";
			break;
		case CompoundAssignStatement::Operation::Multiplication:
			m_source << "*";
			break;
		case CompoundAssignStatement::Operation::Division:
			m_source << "/";
			break;
		case CompoundAssignStatement::Operation::Modulo:
			m_source << "%";
			break;
		case CompoundAssignStatement::Operation::BitwiseAnd:
			m_source << "&";
			break;
		case CompoundAssignStatement::Operation::BitwiseOr:
			m_source << "|";
			break;
		case CompoundAssignStatement::Operation::BitwiseXor:
			m_source << "^";
			break;
		case CompoundAssignStatement::Operation::LeftShift:
			m_source << "<<";
			break;
		case CompoundAssignStatement::Operation::RightShift:
			m_source << ">>";
			break;
		default:
			std::abort();
		}

		m_source << "= ";
		traverse_expression(compound_assign_statement->expression());
		m_source << ";\n";

		return false;
	}

	bool CGenerator::visit_expression_statement(
		const ExpressionStatement *expression_statement)
	{
		m_source << m_indention;
		traverse_expression(expression_statement->expression());
		m_source << ";\n";

		return false;
	}

	bool CGenerator::visit_if_statement(const IfStatement *if_statement)
	{
		m_source << m_indention << "if (";
		traverse_expression(if_statement->condition());
		m_source << ")\n";

		start_scope();
		traverse_statement(if_statement->true_body());
		end_scope();

		if (if_statement->false_body())
		{
			m_source << m_indention << "else\n";

			start_scope();
			traverse_statement(if_statement->false_body());
			end_scope();
		}

		return false;
	}

	bool CGenerator::visit_print_statement(const PrintStatement *print_statement)
	{
		m_source << m_indention << "printf(\"%llu\\n\", ";

		traverse_expression(print_statement->expression());

		m_source << ");\n";

		return false;
	}

	bool CGenerator::visit_return_statement(
		const ReturnStatement *return_statement)
	{
		m_source << m_indention << "return";

		if (return_statement->expression())
		{
			m_source << ' ';
			traverse_expression(return_statement->expression());
		}

		m_source << ";\n";

		return false;
	}

	bool CGenerator::visit_while_statement(const WhileStatement *while_statement)
	{
		m_source << m_indention << "while (";
		traverse_expression(while_statement->condition());
		m_source << ")\n";

		start_scope();
		traverse_statement(while_statement->body());
		end_scope();

		return false;
	}

	void CGenerator::start_scope()
	{
		m_source << m_indention << "{\n";
		m_indention += '\t';
	}

	void CGenerator::end_scope()
	{
		m_indention.pop_back();
		m_source << m_indention << "}\n";
	}

	std::string CGenerator::map_data_type(const DataType &data_type) const
	{
		switch (data_type.kind())
		{
		case DataType::Kind::Bool:
			return "bool";
		case DataType::Kind::Int8:
			return "int8_t";
		case DataType::Kind::Int16:
			return "int16_t";
		case DataType::Kind::Int32:
			return "int32_t";
		case DataType::Kind::Int64:
			return "int64_t";
		case DataType::Kind::Uint8:
			return "uint8_t";
		case DataType::Kind::Uint16:
			return "uint16_t";
		case DataType::Kind::Uint32:
			return "uint32_t";
		case DataType::Kind::Uint64:
			return "uint64_t";
		case DataType::Kind::ISize:
			return "int64_t";
		case DataType::Kind::USize:
			return "uint64_t";
		case DataType::Kind::Float32:
			return "float";
		case DataType::Kind::Float64:
			return "double";
		case DataType::Kind::String:
			return "const char*";
		case DataType::Kind::Void:
			return "void";
		case DataType::Kind::UserDefined:
			return data_type.value();
		default:
			break;
		}

		return "";
	}
} // namespace hyper

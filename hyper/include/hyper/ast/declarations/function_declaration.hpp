/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declaration.hpp"
#include "hyper/ast/forward.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/data_type.hpp"
#include "hyper/source_range.hpp"

#include <string>
#include <vector>

namespace hyper
{
	class FunctionDeclaration final : public Declaration
	{
	public:
		FunctionDeclaration(
			SourceRange source_range,
			Identifier identifier,
			std::vector<DeclarationPtr> arguments,
			DataType return_type,
			StatementPtr body);

		void validate_scope(const ScopeValidator &scope_validator) const override;
		void validate_type(const TypeValidator &type_validator) const override;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::FunctionDeclaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "FunctionDeclaration";
		}

	private:
		Identifier m_identifier;
		std::vector<DeclarationPtr> m_arguments = {};
		DataType m_return_type = {};
		StatementPtr m_body = nullptr;
	};
} // namespace hyper

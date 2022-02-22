/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/declarations/declaration.hpp"
#include "hyper/data_type.hpp"
#include "hyper/identifier.hpp"

#include <span>
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
			std::vector<Declaration *> arguments,
			DataType return_type,
			Statement *body);
		~FunctionDeclaration() override;

		Identifier identifier() const;
		std::span<Declaration *const> arguments() const;
		DataType return_type() const;
		const Statement *body() const;

		constexpr Category class_category() const noexcept override
		{
			return AstNode::Category::FunctionDeclaration;
		}

		constexpr Kind class_kind() const noexcept override
		{
			return AstNode::Kind::Declaration;
		}

		constexpr std::string_view class_name() const noexcept override
		{
			return "FunctionDeclaration";
		}

	private:
		Identifier m_identifier;
		std::vector<Declaration *> m_arguments = {};
		DataType m_return_type = {};
		Statement *m_body = nullptr;
	};
} // namespace hyper

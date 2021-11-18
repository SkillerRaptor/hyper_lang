/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declarations/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"
#include "Hyper/DataType.hpp"

namespace Hyper
{
	class FunctionDeclaration final : public Declaration
	{
	public:
		struct CreateInfo
		{
			std::string name;
			DeclarationList arguments = {};
			DataType return_type = DataType::None;
			StatementPtr body = nullptr;
		};

	public:
		explicit FunctionDeclaration(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(
			std::string_view file,
			const std::string &prefix,
			bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string name() const;
		DataType return_type() const noexcept;
		const DeclarationList &arguments() const;
		const StatementPtr &body() const;

	private:
		std::string m_name;
		DeclarationList m_arguments = {};
		DataType m_return_type = {};
		StatementPtr m_body = nullptr;
	};
} // namespace Hyper

/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declarations/Declaration.hpp"
#include "Hyper/Ast/Forward.hpp"

#include <string>

namespace Hyper
{
	class TranslationUnitDeclaration final : public Declaration
	{
	public:
		struct CreateInfo
		{
			std::string file;
			StatementList statements = {};
		};

	public:
		explicit TranslationUnitDeclaration(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(
			std::string_view file,
			const std::string &prefix,
			bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string file() const;
		const StatementList &statements() const;

	private:
		std::string m_file;
		StatementList m_statements = {};
	};
} // namespace Hyper

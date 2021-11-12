/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declarations/Declaration.hpp"

#include <string>
#include <vector>

namespace Hyper
{
	class TranslationUnitDeclaration final : public Declaration
	{
	public:
		TranslationUnitDeclaration(
			std::string file,
			std::vector<StatementPtr> statements);

		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;

		std::string file() const;
		const std::vector<StatementPtr> &statements() const;

	private:
		std::string m_file;
		std::vector<StatementPtr> m_statements = {};
	};
} // namespace Hyper

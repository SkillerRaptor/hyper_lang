/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Declarations/Declaration.hpp"
#include "Hyper/DataType.hpp"

namespace Hyper
{
	class VariableDeclaration final : public Declaration
	{
	public:
		struct CreateInfo
		{
			std::string name;
			DataType type = DataType::None;
			bool is_immutable = true;
		};

	public:
		explicit VariableDeclaration(CreateInfo create_info);

		void accept(Generator &generator) const override;
		void dump(const std::string &prefix, bool is_self_last) const override;

		Category class_category() const noexcept override;
		std::string_view class_name() const noexcept override;
		std::string class_description() const override;

		std::string name() const;
		DataType type() const noexcept;
		bool is_immutable() const noexcept;

	private:
		std::string m_name;
		DataType m_type = {};
		bool m_is_immutable = true;
	};
} // namespace Hyper

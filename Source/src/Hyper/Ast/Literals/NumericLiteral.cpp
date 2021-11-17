/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/NumericLiteral.hpp"

#include "Hyper/Ast/AstFormatter.hpp"
#include "Hyper/Generators/Generator.hpp"
#include "Hyper/Logger.hpp"

#include <limits>

namespace Hyper
{
	NumericLiteral::NumericLiteral(NumericLiteral::CreateInfo create_info)
		: m_value(create_info.value)
		, m_is_signed(create_info.is_signed)
	{
	}

	void NumericLiteral::accept(Generator &generator) const
	{
		generator.visit(*this);
	}

	void NumericLiteral::dump(const std::string &prefix, bool is_self_last) const
	{
		const std::string current_prefix =
			AstFormatter::format_prefix(*this, prefix, is_self_last);
		Logger::debug("{}", current_prefix);
	}

	AstNode::Category NumericLiteral::class_category() const noexcept
	{
		return AstNode::Category::NumericLiteral;
	}

	std::string_view NumericLiteral::class_name() const noexcept
	{
		return "NumericLiteral";
	}

	std::string NumericLiteral::class_description() const
	{
		uint64_t numeric_value = m_value;
		if (m_is_signed)
		{
			numeric_value +=
				static_cast<uint64_t>(std::numeric_limits<int64_t>::min());
		}

		const std::string extended_value =
			Formatter::format("{}{}", m_is_signed ? "-" : "", numeric_value);
		const std::string value =
			AstFormatter::format_member("value", extended_value);
		const std::string is_signed =
			AstFormatter::format_member("is_signed", m_is_signed);

		return Formatter::format("({}, {})", value, is_signed);
	}

	uint64_t NumericLiteral::value() const noexcept
	{
		return m_value;
	}

	bool NumericLiteral::is_signed() const noexcept
	{
		return m_is_signed;
	}
} // namespace Hyper

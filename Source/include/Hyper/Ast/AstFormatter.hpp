/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Formatter.hpp"

namespace Hyper
{
	class AstNode;

	class AstFormatter
	{
	public:
		static std::string format_prefix(
			const AstNode &node,
			std::string_view prefix,
			bool is_self_last);

		static std::string format_next_prefix(
			std::string_view prefix,
			bool is_self_last);

		template <
			typename T,
			typename =
				decltype(std::declval<std::ostream &>() << std::declval<const T &>)>
		static std::string format_member(std::string_view name, const T &value)
		{
			const std::string colored_name = Formatter::format(
				"{}{}{}", Formatter::s_color_green, name, Formatter::s_color_reset);
			const std::string colored_value = Formatter::format(
				"{}{}{}", Formatter::s_color_yellow, value, Formatter::s_color_reset);
			return Formatter::format("{}={}", colored_name, colored_value);
		}
	};
} // namespace Hyper

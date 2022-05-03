/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <functional>
#include <string_view>
#include <vector>

namespace hyper
{
	class ArgsParser
	{
	public:
		enum class Required : uint8_t
		{
			No = 0,
			Yes
		};

		struct Option
		{
			Required required = Required::Yes;
			std::string_view help_string;
			std::string_view long_name;
			std::string_view short_name;
			std::string_view value_name;
			std::function<bool(std::string_view)> accept_value = {};
		};

		struct Argument
		{
			std::string_view name;
			std::string_view help_string;
			size_t min = 0;
			size_t max = 1;
			std::function<bool(std::string_view)> accept_value = {};
		};

	public:
		ArgsParser();

		bool parse(int argc, char **argv);

		void add_option(
			bool &value,
			std::string_view help_string,
			std::string_view long_name,
			std::string_view short_name);

		void add_option(
			std::string_view &value,
			std::string_view help_string,
			std::string_view long_name,
			std::string_view short_name,
			std::string_view value_name);

		void add_option(
			std::vector<std::string_view> &values,
			std::string_view help_string,
			std::string_view long_name,
			std::string_view short_name,
			std::string_view value_name);

		void add_positional_argument(
			std::vector<std::string_view> &values,
			std::string_view help_string,
			std::string_view name,
			Required required = Required::Yes);

		void set_version(std::string_view version);

	private:
		bool consume_option(
			std::string_view argument,
			bool is_short_option,
			bool is_long_option);

		void print_usage(std::string_view executable_path) const;
		void print_version() const;

	private:
		std::vector<Option> m_options = {};
		std::vector<Argument> m_positional_arguments = {};

		bool m_show_help = false;
		bool m_show_version = false;
		std::string_view m_version;
	};
} // namespace hyper

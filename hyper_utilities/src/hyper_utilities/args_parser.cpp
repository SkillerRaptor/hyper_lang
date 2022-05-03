/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper_utilities/args_parser.hpp"

#include "hyper_utilities/logger.hpp"
#include "hyper_utilities/profiler.hpp"

#include <filesystem>

namespace hyper
{
	ArgsParser::ArgsParser()
	{
		add_option(m_show_help, "Displays the help message and exits", "help", "");
		add_option(m_show_version, "Prints the version", "version", "");
	}

	bool ArgsParser::parse(int argc, char **argv)
	{
		HYPER_PROFILE_FUNCTION();

		size_t current_argument = 1;
		for (; current_argument < static_cast<size_t>(argc); ++current_argument)
		{
			const std::string_view argument = argv[current_argument];
			const bool is_short_option = argument.starts_with("-");
			const bool is_long_option = argument.starts_with("--");
			if (!is_short_option && !is_long_option)
			{
				break;
			}

			if (!consume_option(argument, is_short_option, is_long_option))
			{
				return false;
			}
		}

		if (m_show_help)
		{
			print_usage(argv[0]);
			std::exit(0);
		}

		if (m_show_version)
		{
			print_version();
			std::exit(0);
		}

		size_t required_values_count = 0;
		std::vector<size_t> argument_count = {};
		for (size_t i = 0; i < m_positional_arguments.size(); ++i)
		{
			const Argument &argument = m_positional_arguments[i];
			argument_count.emplace_back(argument.min);
			required_values_count += argument.min;
		}

		const size_t values_left = static_cast<size_t>(argc) - current_argument;
		if (required_values_count > values_left)
		{
			print_usage(argv[0]);
			return false;
		}

		size_t extra_values = values_left - required_values_count;
		for (size_t i = 0; i < m_positional_arguments.size(); ++i)
		{
			const Argument &argument = m_positional_arguments[i];
			const size_t difference =
				std::min(argument.max - argument.min, extra_values);
			argument_count[i] += difference;
			extra_values -= difference;
			if (extra_values == 0)
			{
				break;
			}
		}

		if (extra_values > 0)
		{
			print_usage(argv[0]);
			return false;
		}

		for (size_t i = 0; i < m_positional_arguments.size(); ++i)
		{
			const Argument &argument = m_positional_arguments[i];
			const size_t count = argument_count[i];
			for (size_t j = 0; j < count; ++j)
			{
				const std::string_view value = argv[current_argument + i + j];
				if (argument.accept_value(value))
				{
					continue;
				}

				Logger::error("Invalid value for argument {}", argument.name);
				print_usage(argv[0]);
				return false;
			}
		}

		return true;
	}

	void ArgsParser::add_option(
		bool &value,
		std::string_view help_string,
		std::string_view long_name,
		std::string_view short_name)
	{
		Option option = {
			.required = Required::No,
			.help_string = help_string,
			.long_name = long_name,
			.short_name = short_name,
			.value_name = "",
			.accept_value =
				[&value](std::string_view)
			{
				value = true;
				return true;
			},
		};

		m_options.emplace_back(std::move(option));
	}

	void ArgsParser::add_option(
		std::string_view &value,
		std::string_view help_string,
		std::string_view long_name,
		std::string_view short_name,
		std::string_view value_name)
	{
		Option option = {
			.required = Required::Yes,
			.help_string = help_string,
			.long_name = long_name,
			.short_name = short_name,
			.value_name = value_name,
			.accept_value =
				[&value](std::string_view string)
			{
				value = string;
				return true;
			},
		};

		m_options.emplace_back(std::move(option));
	}

	void ArgsParser::add_option(
		std::vector<std::string_view> &values,
		std::string_view help_string,
		std::string_view long_name,
		std::string_view short_name,
		std::string_view value_name)
	{
		Option option = {
			.required = Required::Yes,
			.help_string = help_string,
			.long_name = long_name,
			.short_name = short_name,
			.value_name = value_name,
			.accept_value =
				[&values](std::string_view string)
			{
				values.emplace_back(string);
				return true;
			},
		};

		m_options.emplace_back(std::move(option));
	}

	void ArgsParser::add_positional_argument(
		std::vector<std::string_view> &values,
		std::string_view help_string,
		std::string_view name,
		ArgsParser::Required required)
	{
		Argument argument = {
			.name = name,
			.help_string = help_string,
			.min = static_cast<size_t>(required == ArgsParser::Required::Yes ? 1 : 0),
			.max = std::numeric_limits<size_t>::max(),
			.accept_value =
				[&values](std::string_view string)
			{
				values.emplace_back(string);
				return true;
			},
		};

		m_positional_arguments.emplace_back(std::move(argument));
	}

	bool ArgsParser::consume_option(
		std::string_view argument,
		bool is_short_option,
		bool is_long_option)
	{
		HYPER_PROFILE_FUNCTION();

		const size_t equal_position = argument.find_first_of("=");
		const bool has_value = equal_position != std::string_view::npos;
		const size_t offset = is_long_option ? 2 : 1;
		const std::string_view option_name = argument.substr(
			offset, (has_value ? equal_position : argument.length()) - offset);

		bool option_found = false;
		for (Option &option : m_options)
		{
			if (is_long_option && !is_short_option)
			{
				if (option.long_name.empty() || option.long_name != option_name)
				{
					continue;
				}
			}

			if (!is_long_option && is_short_option)
			{
				if (option.short_name.empty() || option.short_name != option_name)
				{
					continue;
				}
			}

			if (option.required == Required::No)
			{
				option.accept_value("");
				option_found = true;
				break;
			}

			if (!has_value)
			{
				Logger::error("The argument '{}' requires a value\n", option_name);
				return false;
			}

			const std::string_view value = argument.substr(equal_position + 1);
			option.accept_value(value);
			option_found = true;
			break;
		}

		if (!option_found)
		{
			Logger::error("The argument '{}' is unknown\n", option_name);
			return false;
		}

		return true;
	}

	void ArgsParser::set_version(std::string_view version)
	{
		m_version = version;
	}

	void ArgsParser::print_usage(std::string_view executable_path) const
	{
		Logger::info("Usage:\n");

		std::stringstream usage_stream;
		usage_stream << '\t';
		usage_stream << std::filesystem::path(executable_path).filename().string();

		if (!m_options.empty())
		{
			usage_stream << " [options]";
		}

		for (const Argument &argument : m_positional_arguments)
		{
			bool required = argument.min > 0;
			bool repeated = argument.max > 1;

			if (required && repeated)
			{
				usage_stream << " <";
				usage_stream << argument.name;
				usage_stream << "...>";
				continue;
			}

			if (required)
			{
				usage_stream << " <";
				usage_stream << argument.name;
				usage_stream << ">";
				continue;
			}

			if (repeated)
			{
				usage_stream << " [";
				usage_stream << argument.name;
				usage_stream << "...]";
				continue;
			}

			usage_stream << " [";
			usage_stream << argument.name;
			usage_stream << "]";
		}

		Logger::info("{}\n", usage_stream.str());
		Logger::info("\n");

		if (!m_options.empty())
		{
			Logger::info("Options:\n");

			for (const Option &option : m_options)
			{
				std::stringstream option_stream;
				auto print_argument = [&option_stream, &option]()
				{
					if (option.value_name.empty())
					{
						return;
					}

					option_stream << " ";

					if (option.required == Required::Yes)
					{
						option_stream << "<";
						option_stream << option.value_name;
						option_stream << ">";
						return;
					}

					option_stream << "[";
					option_stream << option.value_name;
					option_stream << "]";
				};

				option_stream << '\t';

				if (!option.short_name.empty())
				{
					option_stream << "-";
					option_stream << option.short_name;
					if (option.long_name.empty())
					{
						print_argument();
					}
				}

				if (!option.short_name.empty() && !option.long_name.empty())
				{
					option_stream << ", ";
				}

				if (!option.long_name.empty())
				{
					option_stream << "--";
					option_stream << option.long_name;
					print_argument();
				}

				if (!option.help_string.empty())
				{
					static constexpr size_t option_width = 30;
					const size_t length = option_width - option_stream.str().length() +
																option.help_string.length() + 2;
					option_stream << std::setw(static_cast<int>(length));
					option_stream << option.help_string;
				}

				Logger::info("{}\n", option_stream.str());
			}

			Logger::info("\n");
		}

		if (!m_positional_arguments.empty())
		{
			Logger::info("Arguments:\n");

			for (const Argument &argument : m_positional_arguments)
			{
				std::stringstream argument_stream;
				argument_stream << "\t";
				argument_stream << argument.name;
				if (!argument.help_string.empty())
				{
					static constexpr size_t argument_width = 32;
					const size_t length = argument_width -
																argument_stream.str().length() +
																argument.help_string.length();
					argument_stream << std::setw(static_cast<int>(length));
					argument_stream << argument.help_string;
				}

				Logger::info("{}\n", argument_stream.str());
			}
		}
	}

	void ArgsParser::print_version() const
	{
		Logger::info("{}\n", m_version);
	}
} // namespace hyper

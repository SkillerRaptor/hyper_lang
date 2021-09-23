/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Lexer.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Utils.hpp"

auto main(int argc, char** argv) -> int
{
	if (argc < 2)
	{
		Hyper::Logger::hyper_fatal("no input files");
		Hyper::Utils::terminate_compilation();
	}

	bool file_found = false;
	for (size_t i = 1; i < static_cast<size_t>(argc); ++i)
	{
		Hyper::Lexer lexer{ argv[1] };
		if (!lexer.initialize())
		{
			continue;
		}

		file_found = true;

		// TODO(SkillerRaptor): Parsing
		
		Hyper::Token token = lexer.next_token();
		while (token.type != Hyper::Token::Type::Eof)
		{
			Hyper::Logger::info("Token", "{} - {}", token.value, token.type);
			token = lexer.next_token();
		}
	}

	if (!file_found)
	{
		Hyper::Logger::hyper_fatal("no input files");
		Hyper::Utils::terminate_compilation();
	}
	
	return EXIT_SUCCESS;
}

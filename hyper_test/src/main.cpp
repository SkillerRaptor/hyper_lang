/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/logger.hpp"
#include "hyper/tester.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		hyper::Logger::error("There is no compiler specified\n");
		return 1;
	}

	const hyper::Tester tester(argv[0], argv[1]);
	return tester.test();
}

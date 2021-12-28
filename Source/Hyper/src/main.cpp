/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

int main(int argc, char **argv)
{
	// TODO: Check if file was passed

	const Hyper::Compiler compiler(argc, argv);
	return compiler.compile();
}

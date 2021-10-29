/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/Declaration.hpp"

#include <ostream>

namespace Hyper
{
	class VariableDeclaration final : public Declaration
	{
	public:
		enum class Type : unsigned char
		{
			None = 0,
			
			Int64
		};

	public:
		VariableDeclaration(std::string identifier, Type type);
		
		void accept(Generator &generator) const override;
		void dump(size_t indent) const override;

		const char *class_name() const noexcept override;
		
		std::string identifier() const;
		Type type() const noexcept;
		
	private:
		std::string m_identifier;
		Type m_type = Type::None;
	};
	
	std::ostream &operator<<(
		std::ostream &ostream,
		const VariableDeclaration::Type &type);
} // namespace Hyper

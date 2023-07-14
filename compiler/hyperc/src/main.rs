/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use hyperc_lexer::Lexer;

use color_eyre::Result;

fn main() -> Result<()> {
    color_eyre::install()?;

    let test_program = r#"
    "#;

    let mut lexer = Lexer::new(test_program);
    let tokens = lexer.lex()?;

    println!("Parsed tokens: {:?}", tokens);

    Ok(())
}

/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

mod utils;

use crate::utils::logger;

use hyperc_lexer::Lexer;

use color_eyre::Result;

fn main() -> Result<()> {
    color_eyre::install()?;
    logger::init(3)?;

    let test_program = r#"
    "#;

    let mut lexer = Lexer::new(test_program);
    let tokens = lexer.lex()?;

    log::info!("Parsed tokens: {:?}", tokens);

    Ok(())
}

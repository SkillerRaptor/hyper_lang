/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

mod lexer;
mod utils;

use crate::{lexer::Lexer, utils::logger};

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

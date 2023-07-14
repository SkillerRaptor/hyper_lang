/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use hyperc_diagnostics::Diagnostic;
use hyperc_lexer::Lexer;

use color_eyre::Result;

fn main() -> Result<()> {
    color_eyre::install()?;

    let test_program = unindent::unindent(
        r#"
        int main() {
            return 0;
        }
        "#,
    );

    let diagnostic = Diagnostic::new("test.c", &test_program);

    let mut lexer = Lexer::new(&diagnostic, &test_program);
    let Some(tokens) = lexer.lex() else {
        return Ok(());
    };

    println!("Parsed tokens: {:#?}", tokens);

    Ok(())
}

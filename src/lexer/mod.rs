/*
 * Copyright (c) 2022, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

mod tests;
pub mod token;

use crate::lexer::token::Token;

use color_eyre::{eyre::bail, Result};

#[derive(Debug)]
pub struct Lexer<'a> {
    text: &'a str,

    current_character: char,
    index: u64,

    line: u64,
    column: u64,
}

impl<'a> Lexer<'a> {
    pub fn new(text: &'a str) -> Self {
        Self {
            text,

            current_character: '\0',
            index: 0,

            line: 1,
            column: 0,
        }
    }

    pub fn lex(&mut self) -> Result<Vec<Token>> {
        let mut tokens = Vec::new();

        while !self.has_reached_end() {
            let token = self.next_token()?;
            if token == Token::Eof {
                break;
            }

            tokens.push(token);
        }

        Ok(tokens)
    }

    fn next_token(&mut self) -> Result<Token> {
        self.advance();
        self.skip_whitespace();

        let token = match self.current_character {
            '[' => Token::BracketLeft,
            ']' => Token::BracketRight,
            '(' => Token::ParenthesisLeft,
            ')' => Token::ParenthesisRight,
            '{' => Token::BraceLeft,
            '}' => Token::BraceRight,
            '.' => {
                if self.peek(0) == '.' && self.peek(1) == '.' {
                    self.advance();
                    self.advance();
                    Token::Ellipsis
                } else {
                    Token::Period
                }
            }
            '&' => match self.peek(0) {
                '&' => {
                    self.advance();
                    Token::LogicalAnd
                }
                '=' => {
                    self.advance();
                    Token::BitwiseAndAssign
                }
                _ => Token::Ampersand,
            },
            '*' => {
                if self.peek(0) == '=' {
                    self.advance();
                    Token::MultiplyAssign
                } else {
                    Token::Asterisk
                }
            }
            '+' => match self.peek(0) {
                '+' => {
                    self.advance();
                    Token::Increment
                }
                '=' => {
                    self.advance();
                    Token::PlusAssign
                }
                _ => Token::Plus,
            },
            '-' => match self.peek(0) {
                '-' => {
                    self.advance();
                    Token::Decrement
                }
                '=' => {
                    self.advance();
                    Token::MinusAssign
                }
                '>' => {
                    self.advance();
                    Token::Arrow
                }
                _ => Token::Minus,
            },
            '~' => Token::Tilde,
            '!' => {
                if self.peek(0) == '=' {
                    self.advance();
                    Token::NotEqual
                } else {
                    Token::ExclamationMark
                }
            }
            '/' => {
                if self.peek(0) == '=' {
                    self.advance();
                    Token::DivideAssign
                } else {
                    Token::Slash
                }
            }
            '%' => {
                if self.peek(0) == '=' {
                    self.advance();
                    Token::ModuloAssign
                } else {
                    Token::Percent
                }
            }
            '<' => match self.peek(0) {
                '<' => {
                    if self.peek(1) == '=' {
                        self.advance();
                        self.advance();
                        Token::LeftShiftAssign
                    } else {
                        self.advance();
                        Token::LeftShift
                    }
                }
                '=' => {
                    self.advance();
                    Token::LessThanOrEqual
                }
                _ => Token::LessThan,
            },
            '>' => match self.peek(0) {
                '>' => {
                    if self.peek(1) == '=' {
                        self.advance();
                        self.advance();
                        Token::RightShiftAssign
                    } else {
                        self.advance();
                        Token::RightShift
                    }
                }
                '=' => {
                    self.advance();
                    Token::GreaterThanOrEqual
                }
                _ => Token::GreaterThan,
            },
            '=' => {
                if self.peek(0) == '=' {
                    self.advance();
                    Token::Equal
                } else {
                    Token::Assign
                }
            }
            '^' => {
                if self.peek(0) == '=' {
                    self.advance();
                    Token::BitwiseXorAssign
                } else {
                    Token::Caret
                }
            }
            '|' => match self.peek(0) {
                '|' => {
                    self.advance();
                    Token::LogicalOr
                }
                '=' => {
                    self.advance();
                    Token::BitwiseOrAssign
                }
                _ => Token::Pipe,
            },
            '?' => Token::QuestionMark,
            ':' => Token::Colon,
            ';' => Token::Semicolon,
            ',' => Token::Comma,
            '#' => {
                if self.peek(0) == '#' {
                    self.advance();
                    Token::DoublePoundSign
                } else {
                    Token::PoundSign
                }
            }
            '_' | 'a'..='z' | 'A'..='Z' => self.lex_identifier_or_keyword(),
            '0'..='9' => self.lex_number_constant()?,
            '\0' => Token::Eof,
            _ => {
                // TODO: Improve error message
                bail!("unexpected token at {}:{}", self.line, self.column)
            }
        };

        Ok(token)
    }

    fn lex_identifier_or_keyword(&mut self) -> Token {
        // TODO: Implement 'Universal character names'

        let mut string = String::new();
        string.push(self.current_character);

        let mut next_char = self.peek(0);
        while next_char == '_' || next_char.is_alphabetic() || next_char.is_ascii_digit() {
            self.advance();
            string.push(next_char);

            next_char = self.peek(0);
        }

        match string.as_str() {
            "auto" => Token::Auto,
            "break" => Token::Break,
            "case" => Token::Case,
            "char" => Token::Char,
            "const" => Token::Const,
            "continue" => Token::Continue,
            "default" => Token::Default,
            "do" => Token::Do,
            "double" => Token::Double,
            "else" => Token::Else,
            "enum" => Token::Enum,
            "extern" => Token::Extern,
            "float" => Token::Float,
            "for" => Token::For,
            "goto" => Token::Goto,
            "if" => Token::If,
            "inline" => Token::Inline,
            "int" => Token::Int,
            "long" => Token::Long,
            "register" => Token::Register,
            "restrict" => Token::Restrict,
            "return" => Token::Return,
            "short" => Token::Short,
            "signed" => Token::Signed,
            "sizeof" => Token::Sizeof,
            "static" => Token::Static,
            "struct" => Token::Struct,
            "switch" => Token::Switch,
            "typedef" => Token::Typedef,
            "union" => Token::Union,
            "unsigned" => Token::Unsigned,
            "void" => Token::Void,
            "volatile" => Token::Volatile,
            "while" => Token::While,
            _ => Token::Identifier(string),
        }
    }

    fn lex_number_constant(&mut self) -> Result<Token> {
        let mut integer = String::new();
        integer.push(self.current_character);

        if self.current_character == '0' {
            let next_char = self.peek(0);
            if next_char == 'x' || next_char == 'X' {
                self.advance();
                integer.push(self.current_character);

                let mut next_char = self.peek(0);
                if next_char.is_ascii_digit()
                    || ('a'..='f').contains(&next_char)
                    || ('A'..='F').contains(&next_char)
                {
                    while next_char.is_ascii_digit()
                        || ('a'..='f').contains(&next_char)
                        || ('A'..='F').contains(&next_char)
                    {
                        self.advance();
                        integer.push(next_char);

                        next_char = self.peek(0);
                    }
                } else {
                    // TODO: Improve error message
                    bail!("unclosed hexadecimal constant");
                }
            } else if next_char.is_ascii_digit() {
                let mut next_char = self.peek(0);
                while ('0'..='7').contains(&next_char) {
                    self.advance();
                    integer.push(next_char);

                    next_char = self.peek(0);
                }
            }
        } else {
            let mut next_char = self.peek(0);
            while next_char.is_ascii_digit() {
                self.advance();
                integer.push(next_char);

                next_char = self.peek(0);
            }
        }

        Ok(Token::Number(integer))
    }

    // Lexer specific
    fn advance(&mut self) {
        if self.has_reached_end() {
            self.current_character = '\0';
            return;
        }

        if self.current_character == '\n' {
            self.line += 1;
            self.column = 0;
        }

        if self.current_character == '\t' {
            self.column += 1;
        }

        self.column += 1;

        self.current_character = self.text.as_bytes()[self.index as usize] as char;
        self.index += 1;
    }

    fn peek(&self, extra_offset: usize) -> char {
        if (self.index as usize + extra_offset) >= self.text.len() {
            return '\0';
        }

        self.text.as_bytes()[self.index as usize + extra_offset] as char
    }

    fn skip_whitespace(&mut self) {
        while self.current_character == ' '
            || self.current_character == '\t'
            || self.current_character == '\n'
            || self.current_character == '\r'
        {
            self.advance();
        }
    }

    fn has_reached_end(&self) -> bool {
        self.index as usize >= self.text.len()
    }
}

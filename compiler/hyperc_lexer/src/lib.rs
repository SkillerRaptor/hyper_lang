/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

mod tests;
pub mod token;

use crate::token::{BinaryOperation, Delimiter, Keyword, LiteralKind, Token, TokenKind};

use hyperc_diagnostics::{annotation::Annotation, errors::ErrorCode, report::Report, Diagnostic};
use hyperc_span::Span;

#[derive(Debug)]
pub struct Lexer<'a> {
    diagnostic: &'a Diagnostic,
    text: &'a str,

    current_character: char,
    index: usize,

    line: u64,
    column: u64,
}

impl<'a> Lexer<'a> {
    pub fn new(diagnostic: &'a Diagnostic, text: &'a str) -> Self {
        Self {
            diagnostic,
            text,

            current_character: '\0',
            index: 0,

            line: 1,
            column: 0,
        }
    }

    pub fn lex(&mut self) -> Option<Vec<Token>> {
        let mut tokens = Vec::new();

        while !self.has_reached_end() {
            let token = self.next_token()?;
            if token.kind() == TokenKind::Eof {
                break;
            }

            tokens.push(token);
        }

        Some(tokens)
    }

    fn next_token(&mut self) -> Option<Token> {
        self.advance();
        self.skip_whitespace();

        let start_index = self.index - 1;

        let kind = match self.current_character {
            '[' => TokenKind::OpenDelimiter(Delimiter::Bracket),
            ']' => TokenKind::CloseDelimiter(Delimiter::Bracket),
            '(' => TokenKind::OpenDelimiter(Delimiter::Parenthesis),
            ')' => TokenKind::CloseDelimiter(Delimiter::Parenthesis),
            '{' => TokenKind::OpenDelimiter(Delimiter::Brace),
            '}' => TokenKind::CloseDelimiter(Delimiter::Brace),
            '.' => {
                if self.peek(0) == '.' && self.peek(1) == '.' {
                    self.advance();
                    self.advance();
                    TokenKind::Ellipsis
                } else {
                    TokenKind::Period
                }
            }
            '&' => match self.peek(0) {
                '&' => {
                    self.advance();
                    TokenKind::LogicalAnd
                }
                '=' => {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::And)
                }
                _ => TokenKind::BinaryOperation(BinaryOperation::And),
            },
            '*' => {
                if self.peek(0) == '=' {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Star)
                } else {
                    TokenKind::BinaryOperation(BinaryOperation::Star)
                }
            }
            '+' => match self.peek(0) {
                '+' => {
                    self.advance();
                    TokenKind::Increment
                }
                '=' => {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Plus)
                }
                _ => TokenKind::BinaryOperation(BinaryOperation::Plus),
            },
            '-' => match self.peek(0) {
                '-' => {
                    self.advance();
                    TokenKind::Decrement
                }
                '=' => {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Minus)
                }
                '>' => {
                    self.advance();
                    TokenKind::Arrow
                }
                _ => TokenKind::BinaryOperation(BinaryOperation::Minus),
            },
            '~' => TokenKind::Tilde,
            '!' => {
                if self.peek(0) == '=' {
                    self.advance();
                    TokenKind::NotEqual
                } else {
                    TokenKind::ExclamationMark
                }
            }
            '/' => match self.peek(0) {
                '/' => {
                    self.advance();
                    while self.peek(0) != '\n' {
                        self.advance();
                    }

                    return self.next_token();
                }
                '=' => {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Slash)
                }
                _ => TokenKind::BinaryOperation(BinaryOperation::Slash),
            },
            '%' => {
                if self.peek(0) == '=' {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Percent)
                } else {
                    TokenKind::BinaryOperation(BinaryOperation::Percent)
                }
            }
            '<' => match self.peek(0) {
                '<' => {
                    if self.peek(1) == '=' {
                        self.advance();
                        self.advance();
                        TokenKind::BinaryOperationEqual(BinaryOperation::LeftShift)
                    } else {
                        self.advance();
                        TokenKind::BinaryOperation(BinaryOperation::LeftShift)
                    }
                }
                '=' => {
                    self.advance();
                    TokenKind::LessThanOrEqual
                }
                _ => TokenKind::LessThan,
            },
            '>' => match self.peek(0) {
                '>' => {
                    if self.peek(1) == '=' {
                        self.advance();
                        self.advance();
                        TokenKind::BinaryOperationEqual(BinaryOperation::RightShift)
                    } else {
                        self.advance();
                        TokenKind::BinaryOperation(BinaryOperation::RightShift)
                    }
                }
                '=' => {
                    self.advance();
                    TokenKind::GreaterThanOrEqual
                }
                _ => TokenKind::GreaterThan,
            },
            '=' => {
                if self.peek(0) == '=' {
                    self.advance();
                    TokenKind::Equal
                } else {
                    TokenKind::Assign
                }
            }
            '^' => {
                if self.peek(0) == '=' {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Caret)
                } else {
                    TokenKind::BinaryOperation(BinaryOperation::Caret)
                }
            }
            '|' => match self.peek(0) {
                '|' => {
                    self.advance();
                    TokenKind::LogicalOr
                }
                '=' => {
                    self.advance();
                    TokenKind::BinaryOperationEqual(BinaryOperation::Or)
                }
                _ => TokenKind::BinaryOperation(BinaryOperation::Or),
            },
            '?' => TokenKind::QuestionMark,
            ':' => TokenKind::Colon,
            ';' => TokenKind::Semicolon,
            ',' => TokenKind::Comma,
            '#' => {
                if self.peek(0) == '#' {
                    self.advance();
                    TokenKind::DoublePoundSign
                } else {
                    TokenKind::PoundSign
                }
            }
            '"' => self.lex_string_literal()?,
            '_' | 'a'..='z' | 'A'..='Z' => self.lex_identifier_or_keyword(),
            '0'..='9' => self.lex_number_constant()?,
            '\0' => TokenKind::Eof,
            _ => {
                let span = Span::new(start_index, self.index);

                let error = "unexpected token";
                let report = Report::error()
                    .with_error_code(ErrorCode::E0001(self.current_character.to_string()))
                    .with_annotations(vec![Annotation::primary(span, error.clone())]);
                self.diagnostic.report(report);

                return None;
            }
        };

        let span = Span::new(start_index, self.index);
        let token = Token::new(kind, span);

        Some(token)
    }

    fn lex_string_literal(&mut self) -> Option<TokenKind> {
        let start_index = self.index - 1;

        let mut next_char = self.peek(0);
        while next_char != '"' {
            if self.has_reached_end() {
                let span = Span::new(start_index, self.index - 1);

                let error = "unclosed string";
                let report = Report::error()
                    .with_error_code(ErrorCode::E0003)
                    .with_annotations(vec![Annotation::primary(span, error)]);
                self.diagnostic.report(report);

                return None;
            }

            self.advance();
            next_char = self.peek(0);
        }

        self.advance();

        Some(TokenKind::Literal(LiteralKind::String))
    }

    fn lex_identifier_or_keyword(&mut self) -> TokenKind {
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
            "auto" => TokenKind::Identifier(Keyword::Auto),
            "break" => TokenKind::Identifier(Keyword::Break),
            "case" => TokenKind::Identifier(Keyword::Case),
            "char" => TokenKind::Identifier(Keyword::Char),
            "const" => TokenKind::Identifier(Keyword::Const),
            "continue" => TokenKind::Identifier(Keyword::Continue),
            "default" => TokenKind::Identifier(Keyword::Default),
            "do" => TokenKind::Identifier(Keyword::Do),
            "double" => TokenKind::Identifier(Keyword::Double),
            "else" => TokenKind::Identifier(Keyword::Else),
            "enum" => TokenKind::Identifier(Keyword::Enum),
            "extern" => TokenKind::Identifier(Keyword::Extern),
            "float" => TokenKind::Identifier(Keyword::Float),
            "for" => TokenKind::Identifier(Keyword::For),
            "goto" => TokenKind::Identifier(Keyword::Goto),
            "if" => TokenKind::Identifier(Keyword::If),
            "inline" => TokenKind::Identifier(Keyword::Inline),
            "int" => TokenKind::Identifier(Keyword::Int),
            "long" => TokenKind::Identifier(Keyword::Long),
            "register" => TokenKind::Identifier(Keyword::Register),
            "restrict" => TokenKind::Identifier(Keyword::Restrict),
            "return" => TokenKind::Identifier(Keyword::Return),
            "short" => TokenKind::Identifier(Keyword::Short),
            "signed" => TokenKind::Identifier(Keyword::Signed),
            "sizeof" => TokenKind::Identifier(Keyword::Sizeof),
            "static" => TokenKind::Identifier(Keyword::Static),
            "struct" => TokenKind::Identifier(Keyword::Struct),
            "switch" => TokenKind::Identifier(Keyword::Switch),
            "typedef" => TokenKind::Identifier(Keyword::Typedef),
            "union" => TokenKind::Identifier(Keyword::Union),
            "unsigned" => TokenKind::Identifier(Keyword::Unsigned),
            "void" => TokenKind::Identifier(Keyword::Void),
            "volatile" => TokenKind::Identifier(Keyword::Volatile),
            "while" => TokenKind::Identifier(Keyword::While),
            _ => TokenKind::Identifier(Keyword::None),
        }
    }

    fn lex_number_constant(&mut self) -> Option<TokenKind> {
        let start_index = self.index - 1;

        if self.current_character == '0' {
            let next_char = self.peek(0);
            if next_char == 'x' || next_char == 'X' {
                self.advance();

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
                        next_char = self.peek(0);
                    }
                } else {
                    let span = Span::new(start_index, self.index);

                    let error = "unclosed hexadecimal";
                    let report = Report::error()
                        .with_error_code(ErrorCode::E0002)
                        .with_annotations(vec![Annotation::primary(span, error)]);
                    self.diagnostic.report(report);

                    return None;
                }
            } else if next_char.is_ascii_digit() {
                let mut next_char = self.peek(0);
                while ('0'..='7').contains(&next_char) {
                    self.advance();
                    next_char = self.peek(0);
                }
            }
        } else {
            let mut next_char = self.peek(0);
            while next_char.is_ascii_digit() {
                self.advance();
                next_char = self.peek(0);
            }
        }

        // Lex suffix
        let mut next_char = self.peek(0);
        match next_char {
            'u' | 'U' => {
                self.advance();
                next_char = self.peek(0);
                if next_char == 'l' || next_char == 'L' {
                    self.advance();
                    next_char = self.peek(0);
                    if next_char == 'l' || next_char == 'L' {
                        self.advance();
                    }
                }
            }
            'l' | 'L' => {
                self.advance();
                next_char = self.peek(0);
                if next_char == 'l' || next_char == 'L' {
                    self.advance();
                    next_char = self.peek(0);
                }

                if next_char == 'u' || next_char == 'U' {
                    self.advance();
                }
            }
            _ => {}
        }

        Some(TokenKind::Literal(LiteralKind::Number))
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

        self.current_character = self.text.as_bytes()[self.index] as char;
        self.index += 1;
    }

    fn peek(&self, extra_offset: usize) -> char {
        if (self.index + extra_offset) >= self.text.len() {
            return '\0';
        }

        self.text.as_bytes()[self.index + extra_offset] as char
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
        self.index >= self.text.len()
    }
}

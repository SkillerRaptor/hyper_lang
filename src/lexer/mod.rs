/*
 * Copyright (c) 2022, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

pub mod token;

use crate::lexer::token::Token;

use color_eyre::Result;

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

        loop {
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

        println!(
            "'{}', '{}', '{}'",
            self.current_character,
            self.peek(0),
            self.peek(1)
        );

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
            _ => Token::Eof,
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn token_auto() {
        let text = "auto auto";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Auto);
        assert_eq!(tokens[1], Token::Auto);
    }

    #[test]
    fn token_break() {
        let text = "break break";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Break);
        assert_eq!(tokens[1], Token::Break);
    }

    #[test]
    fn token_case() {
        let text = "case case";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Case);
        assert_eq!(tokens[1], Token::Case);
    }

    #[test]
    fn token_char() {
        let text = "char char";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Char);
        assert_eq!(tokens[1], Token::Char);
    }

    #[test]
    fn token_const() {
        let text = "const const";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Const);
        assert_eq!(tokens[1], Token::Const);
    }

    #[test]
    fn token_continue() {
        let text = "continue continue";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Continue);
        assert_eq!(tokens[1], Token::Continue);
    }

    #[test]
    fn token_default() {
        let text = "default default";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Default);
        assert_eq!(tokens[1], Token::Default);
    }

    #[test]
    fn token_do() {
        let text = "do do";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Do);
        assert_eq!(tokens[1], Token::Do);
    }

    #[test]
    fn token_double() {
        let text = "double double";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Double);
        assert_eq!(tokens[1], Token::Double);
    }

    #[test]
    fn token_else() {
        let text = "else else";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Else);
        assert_eq!(tokens[1], Token::Else);
    }

    #[test]
    fn token_enum() {
        let text = "enum enum";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Enum);
        assert_eq!(tokens[1], Token::Enum);
    }

    #[test]
    fn token_extern() {
        let text = "extern extern";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Extern);
        assert_eq!(tokens[1], Token::Extern);
    }

    #[test]
    fn token_float() {
        let text = "float float";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Float);
        assert_eq!(tokens[1], Token::Float);
    }

    #[test]
    fn token_for() {
        let text = "for for";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::For);
        assert_eq!(tokens[1], Token::For);
    }

    #[test]
    fn token_goto() {
        let text = "goto goto";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Goto);
        assert_eq!(tokens[1], Token::Goto);
    }

    #[test]
    fn token_if() {
        let text = "if if";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::If);
        assert_eq!(tokens[1], Token::If);
    }

    #[test]
    fn token_inline() {
        let text = "inline inline";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Inline);
        assert_eq!(tokens[1], Token::Inline);
    }

    #[test]
    fn token_int() {
        let text = "int int";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Int);
        assert_eq!(tokens[1], Token::Int);
    }

    #[test]
    fn token_long() {
        let text = "long long";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Long);
        assert_eq!(tokens[1], Token::Long);
    }

    #[test]
    fn token_register() {
        let text = "register register";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Register);
        assert_eq!(tokens[1], Token::Register);
    }

    #[test]
    fn token_restrict() {
        let text = "restrict restrict";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Restrict);
        assert_eq!(tokens[1], Token::Restrict);
    }

    #[test]
    fn token_return() {
        let text = "return return";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Return);
        assert_eq!(tokens[1], Token::Return);
    }

    #[test]
    fn token_short() {
        let text = "short short";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Short);
        assert_eq!(tokens[1], Token::Short);
    }

    #[test]
    fn token_signed() {
        let text = "signed signed";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Signed);
        assert_eq!(tokens[1], Token::Signed);
    }

    #[test]
    fn token_sizeof() {
        let text = "sizeof sizeof";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Sizeof);
        assert_eq!(tokens[1], Token::Sizeof);
    }

    #[test]
    fn token_static() {
        let text = "static static";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Static);
        assert_eq!(tokens[1], Token::Static);
    }

    #[test]
    fn token_struct() {
        let text = "struct struct";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Struct);
        assert_eq!(tokens[1], Token::Struct);
    }

    #[test]
    fn token_switch() {
        let text = "switch switch";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Switch);
        assert_eq!(tokens[1], Token::Switch);
    }

    #[test]
    fn token_typedef() {
        let text = "typedef typedef";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Typedef);
        assert_eq!(tokens[1], Token::Typedef);
    }

    #[test]
    fn token_union() {
        let text = "union union";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Union);
        assert_eq!(tokens[1], Token::Union);
    }

    #[test]
    fn token_unsigned() {
        let text = "unsigned unsigned";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Unsigned);
        assert_eq!(tokens[1], Token::Unsigned);
    }

    #[test]
    fn token_void() {
        let text = "void void";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Void);
        assert_eq!(tokens[1], Token::Void);
    }

    #[test]
    fn token_volatile() {
        let text = "volatile volatile";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Volatile);
        assert_eq!(tokens[1], Token::Volatile);
    }

    #[test]
    fn token_while() {
        let text = "while while";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::While);
        assert_eq!(tokens[1], Token::While);
    }

    #[test]
    fn token_keywords() {
        let text = r#"
        auto
        break
        case
        char
        const
        continue
        default
        do
        double
        else
        enum
        extern
        float
        for
        goto
        if
        inline
        int
        long
        register
        restrict
        return
        short
        signed
        sizeof
        static
        struct
        switch
        typedef
        union
        unsigned
        void
        volatile
        while
        "#;

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 34);
        assert_eq!(tokens[0], Token::Auto);
        assert_eq!(tokens[1], Token::Break);
        assert_eq!(tokens[2], Token::Case);
        assert_eq!(tokens[3], Token::Char);
        assert_eq!(tokens[4], Token::Const);
        assert_eq!(tokens[5], Token::Continue);
        assert_eq!(tokens[6], Token::Default);
        assert_eq!(tokens[7], Token::Do);
        assert_eq!(tokens[8], Token::Double);
        assert_eq!(tokens[9], Token::Else);
        assert_eq!(tokens[10], Token::Enum);
        assert_eq!(tokens[11], Token::Extern);
        assert_eq!(tokens[12], Token::Float);
        assert_eq!(tokens[13], Token::For);
        assert_eq!(tokens[14], Token::Goto);
        assert_eq!(tokens[15], Token::If);
        assert_eq!(tokens[16], Token::Inline);
        assert_eq!(tokens[17], Token::Int);
        assert_eq!(tokens[18], Token::Long);
        assert_eq!(tokens[19], Token::Register);
        assert_eq!(tokens[20], Token::Restrict);
        assert_eq!(tokens[21], Token::Return);
        assert_eq!(tokens[22], Token::Short);
        assert_eq!(tokens[23], Token::Signed);
        assert_eq!(tokens[24], Token::Sizeof);
        assert_eq!(tokens[25], Token::Static);
        assert_eq!(tokens[26], Token::Struct);
        assert_eq!(tokens[27], Token::Switch);
        assert_eq!(tokens[28], Token::Typedef);
        assert_eq!(tokens[29], Token::Union);
        assert_eq!(tokens[30], Token::Unsigned);
        assert_eq!(tokens[31], Token::Void);
        assert_eq!(tokens[32], Token::Volatile);
        assert_eq!(tokens[33], Token::While);
    }

    #[test]
    fn token_identifier() {
        let text = "foo bar";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[1], Token::Identifier("bar".to_string()));
    }

    #[test]
    fn token_bracket_left() {
        let text = "[ [";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BracketLeft);
        assert_eq!(tokens[1], Token::BracketLeft);
    }

    #[test]
    fn token_bracket_right() {
        let text = "] ]";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BracketRight);
        assert_eq!(tokens[1], Token::BracketRight);
    }

    #[test]
    fn token_parenthesis_left() {
        let text = "( (";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::ParenthesisLeft);
        assert_eq!(tokens[1], Token::ParenthesisLeft);
    }

    #[test]
    fn token_parenthesis_right() {
        let text = ") )";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::ParenthesisRight);
        assert_eq!(tokens[1], Token::ParenthesisRight);
    }

    #[test]
    fn token_brace_left() {
        let text = "{ {";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BraceLeft);
        assert_eq!(tokens[1], Token::BraceLeft);
    }

    #[test]
    fn token_brace_right() {
        let text = "} }";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BraceRight);
        assert_eq!(tokens[1], Token::BraceRight);
    }

    #[test]
    fn token_period() {
        let text = ". .";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Period);
        assert_eq!(tokens[1], Token::Period);
    }

    #[test]
    fn token_arrow() {
        let text = "-> ->";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Arrow);
        assert_eq!(tokens[1], Token::Arrow);
    }

    #[test]
    fn token_increment() {
        let text = "++ ++";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Increment);
        assert_eq!(tokens[1], Token::Increment);
    }

    #[test]
    fn token_decrement() {
        let text = "-- --";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Decrement);
        assert_eq!(tokens[1], Token::Decrement);
    }

    #[test]
    fn token_ampersand() {
        let text = "& &";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Ampersand);
        assert_eq!(tokens[1], Token::Ampersand);
    }

    #[test]
    fn token_asterisk() {
        let text = "* *";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Asterisk);
        assert_eq!(tokens[1], Token::Asterisk);
    }

    #[test]
    fn token_plus() {
        let text = "+ +";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Plus);
        assert_eq!(tokens[1], Token::Plus);
    }

    #[test]
    fn token_minus() {
        let text = "- -";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Minus);
        assert_eq!(tokens[1], Token::Minus);
    }

    #[test]
    fn token_tilde() {
        let text = "~ ~";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Tilde);
        assert_eq!(tokens[1], Token::Tilde);
    }

    #[test]
    fn token_exclamation_mark() {
        let text = "! !";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::ExclamationMark);
        assert_eq!(tokens[1], Token::ExclamationMark);
    }

    #[test]
    fn token_slash() {
        let text = "/ /";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Slash);
        assert_eq!(tokens[1], Token::Slash);
    }

    #[test]
    fn token_percent() {
        let text = "% %";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Percent);
        assert_eq!(tokens[1], Token::Percent);
    }

    #[test]
    fn token_left_shift() {
        let text = "<< <<";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::LeftShift);
        assert_eq!(tokens[1], Token::LeftShift);
    }

    #[test]
    fn token_right_shift() {
        let text = ">> >>";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::RightShift);
        assert_eq!(tokens[1], Token::RightShift);
    }

    #[test]
    fn token_less_than() {
        let text = "< <";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::LessThan);
        assert_eq!(tokens[1], Token::LessThan);
    }

    #[test]
    fn token_greater_than() {
        let text = "> >";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::GreaterThan);
        assert_eq!(tokens[1], Token::GreaterThan);
    }

    #[test]
    fn token_less_than_or_equal() {
        let text = "<= <=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::LessThanOrEqual);
        assert_eq!(tokens[1], Token::LessThanOrEqual);
    }

    #[test]
    fn token_greater_than_or_equal() {
        let text = ">= >=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::GreaterThanOrEqual);
        assert_eq!(tokens[1], Token::GreaterThanOrEqual);
    }

    #[test]
    fn token_equal() {
        let text = "== ==";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Equal);
        assert_eq!(tokens[1], Token::Equal);
    }

    #[test]
    fn token_not_equal() {
        let text = "!= !=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::NotEqual);
        assert_eq!(tokens[1], Token::NotEqual);
    }

    #[test]
    fn token_caret() {
        let text = "^ ^";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Caret);
        assert_eq!(tokens[1], Token::Caret);
    }

    #[test]
    fn token_pipe() {
        let text = "| |";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Pipe);
        assert_eq!(tokens[1], Token::Pipe);
    }

    #[test]
    fn token_logical_and() {
        let text = "&& &&";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::LogicalAnd);
        assert_eq!(tokens[1], Token::LogicalAnd);
    }

    #[test]
    fn token_logical_or() {
        let text = "|| ||";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::LogicalOr);
        assert_eq!(tokens[1], Token::LogicalOr);
    }

    #[test]
    fn token_question_mark() {
        let text = "? ?";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::QuestionMark);
        assert_eq!(tokens[1], Token::QuestionMark);
    }

    #[test]
    fn token_colon() {
        let text = ": :";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Colon);
        assert_eq!(tokens[1], Token::Colon);
    }

    #[test]
    fn token_semicolon() {
        let text = "; ;";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Semicolon);
        assert_eq!(tokens[1], Token::Semicolon);
    }

    #[test]
    fn token_dot() {
        let text = ". .";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Period);
        assert_eq!(tokens[1], Token::Period);
    }

    #[test]
    fn token_ellipsis() {
        let text = "... ...";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Ellipsis);
        assert_eq!(tokens[1], Token::Ellipsis);
    }

    #[test]
    fn token_assign() {
        let text = "= =";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Assign);
        assert_eq!(tokens[1], Token::Assign);
    }

    #[test]
    fn token_multiply_assign() {
        let text = "*= *=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::MultiplyAssign);
        assert_eq!(tokens[1], Token::MultiplyAssign);
    }

    #[test]
    fn token_divide_assign() {
        let text = "/= /=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::DivideAssign);
        assert_eq!(tokens[1], Token::DivideAssign);
    }

    #[test]
    fn token_modulo_assign() {
        let text = "%= %=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::ModuloAssign);
        assert_eq!(tokens[1], Token::ModuloAssign);
    }

    #[test]
    fn token_plus_assign() {
        let text = "+= +=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::PlusAssign);
        assert_eq!(tokens[1], Token::PlusAssign);
    }

    #[test]
    fn token_minus_assign() {
        let text = "-= -=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::MinusAssign);
        assert_eq!(tokens[1], Token::MinusAssign);
    }

    #[test]
    fn token_left_shift_assign() {
        let text = "<<= <<=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::LeftShiftAssign);
        assert_eq!(tokens[1], Token::LeftShiftAssign);
    }

    #[test]
    fn token_right_shift_assign() {
        let text = ">>= >>=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::RightShiftAssign);
        assert_eq!(tokens[1], Token::RightShiftAssign);
    }

    #[test]
    fn token_bitwise_and_assign() {
        let text = "&= &=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BitwiseAndAssign);
        assert_eq!(tokens[1], Token::BitwiseAndAssign);
    }

    #[test]
    fn token_bitwise_xor_assign() {
        let text = "^= ^=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BitwiseXorAssign);
        assert_eq!(tokens[1], Token::BitwiseXorAssign);
    }

    #[test]
    fn token_bitwise_or_assign() {
        let text = "|= |=";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::BitwiseOrAssign);
        assert_eq!(tokens[1], Token::BitwiseOrAssign);
    }

    #[test]
    fn token_comma() {
        let text = ", ,";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Comma);
        assert_eq!(tokens[1], Token::Comma);
    }

    #[test]
    fn token_pound_sign() {
        let text = "# #";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::PoundSign);
        assert_eq!(tokens[1], Token::PoundSign);
    }

    #[test]
    fn token_double_pound_sign() {
        let text = "## ##";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::DoublePoundSign);
        assert_eq!(tokens[1], Token::DoublePoundSign);
    }

    #[test]
    fn token_punctuators() {
        let text = r#"
        [
        ]
        (
        )
        {
        }
        .
        ->
        ++
        --
        &
        *
        +
        -
        ~
        !
        /
        %
        <<
        >>
        <
        >
        <=
        >=
        ==
        !=
        ^
        |
        &&
        ||
        ?
        :
        ;
        ...
        =
        *=
        /=
        %=
        +=
        -=
        <<=
        >>=
        &=
        ^=
        |=
        ,
        #
        ##
        "#;

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 48);
        assert_eq!(tokens[0], Token::BracketLeft);
        assert_eq!(tokens[1], Token::BracketRight);
        assert_eq!(tokens[2], Token::ParenthesisLeft);
        assert_eq!(tokens[3], Token::ParenthesisRight);
        assert_eq!(tokens[4], Token::BraceLeft);
        assert_eq!(tokens[5], Token::BraceRight);
        assert_eq!(tokens[6], Token::Period);
        assert_eq!(tokens[7], Token::Arrow);
        assert_eq!(tokens[8], Token::Increment);
        assert_eq!(tokens[9], Token::Decrement);
        assert_eq!(tokens[10], Token::Ampersand);
        assert_eq!(tokens[11], Token::Asterisk);
        assert_eq!(tokens[12], Token::Plus);
        assert_eq!(tokens[13], Token::Minus);
        assert_eq!(tokens[14], Token::Tilde);
        assert_eq!(tokens[15], Token::ExclamationMark);
        assert_eq!(tokens[16], Token::Slash);
        assert_eq!(tokens[17], Token::Percent);
        assert_eq!(tokens[18], Token::LeftShift);
        assert_eq!(tokens[19], Token::RightShift);
        assert_eq!(tokens[20], Token::LessThan);
        assert_eq!(tokens[21], Token::GreaterThan);
        assert_eq!(tokens[22], Token::LessThanOrEqual);
        assert_eq!(tokens[23], Token::GreaterThanOrEqual);
        assert_eq!(tokens[24], Token::Equal);
        assert_eq!(tokens[25], Token::NotEqual);
        assert_eq!(tokens[26], Token::Caret);
        assert_eq!(tokens[27], Token::Pipe);
        assert_eq!(tokens[28], Token::LogicalAnd);
        assert_eq!(tokens[29], Token::LogicalOr);
        assert_eq!(tokens[30], Token::QuestionMark);
        assert_eq!(tokens[31], Token::Colon);
        assert_eq!(tokens[32], Token::Semicolon);
        assert_eq!(tokens[33], Token::Ellipsis);
        assert_eq!(tokens[34], Token::Assign);
        assert_eq!(tokens[35], Token::MultiplyAssign);
        assert_eq!(tokens[36], Token::DivideAssign);
        assert_eq!(tokens[37], Token::ModuloAssign);
        assert_eq!(tokens[38], Token::PlusAssign);
        assert_eq!(tokens[39], Token::MinusAssign);
        assert_eq!(tokens[40], Token::LeftShiftAssign);
        assert_eq!(tokens[41], Token::RightShiftAssign);
        assert_eq!(tokens[42], Token::BitwiseAndAssign);
        assert_eq!(tokens[43], Token::BitwiseXorAssign);
        assert_eq!(tokens[44], Token::BitwiseOrAssign);
        assert_eq!(tokens[45], Token::Comma);
        assert_eq!(tokens[46], Token::PoundSign);
        assert_eq!(tokens[47], Token::DoublePoundSign);
    }
}

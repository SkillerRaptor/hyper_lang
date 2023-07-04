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

        let token = match self.current_character {
            '_' | 'a'..='z' | 'A'..='Z' => self.lex_identifier_or_keyword(),
            _ => Token::Eof,
        };

        Ok(token)
    }

    fn lex_identifier_or_keyword(&mut self) -> Token {
        // TODO: Implement 'Universal character names'

        let mut string = String::new();
        string.push(self.current_character);

        let mut next_char = self.peek();
        while next_char == '_' || next_char.is_alphabetic() || next_char.is_ascii_digit() {
            self.advance();
            string.push(next_char);

            next_char = self.peek();
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

    fn peek(&self) -> char {
        if self.has_reached_end() {
            return '\0';
        }

        self.text.as_bytes()[self.index as usize] as char
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
    fn token_identifier() {
        let text = "foo bar";

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[1], Token::Identifier("bar".to_string()));
    }

    #[test]
    fn token_keyword_identifier() {
        let text = r#"
        foo
        auto
        foo
        break
        foo
        case
        foo
        char
        foo
        const
        foo
        continue
        foo
        default
        foo
        do
        foo
        double
        foo
        else
        foo
        enum
        foo
        extern
        foo
        float
        foo
        for
        foo
        goto
        foo
        if
        foo
        inline
        foo
        int
        foo
        long
        foo
        register
        foo
        restrict
        foo
        return
        foo
        short
        foo
        signed
        foo
        sizeof
        foo
        static
        foo
        struct
        foo
        switch
        foo
        typedef
        foo
        union
        foo
        unsigned
        foo
        void
        foo
        volatile
        foo
        while
        foo
        "#;

        let mut lexer = Lexer::new(text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 69);
        assert_eq!(tokens[0], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[1], Token::Auto);
        assert_eq!(tokens[2], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[3], Token::Break);
        assert_eq!(tokens[4], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[5], Token::Case);
        assert_eq!(tokens[6], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[7], Token::Char);
        assert_eq!(tokens[8], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[9], Token::Const);
        assert_eq!(tokens[10], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[11], Token::Continue);
        assert_eq!(tokens[12], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[13], Token::Default);
        assert_eq!(tokens[14], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[15], Token::Do);
        assert_eq!(tokens[16], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[17], Token::Double);
        assert_eq!(tokens[18], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[19], Token::Else);
        assert_eq!(tokens[20], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[21], Token::Enum);
        assert_eq!(tokens[22], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[23], Token::Extern);
        assert_eq!(tokens[24], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[25], Token::Float);
        assert_eq!(tokens[26], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[27], Token::For);
        assert_eq!(tokens[28], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[29], Token::Goto);
        assert_eq!(tokens[30], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[31], Token::If);
        assert_eq!(tokens[32], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[33], Token::Inline);
        assert_eq!(tokens[34], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[35], Token::Int);
        assert_eq!(tokens[36], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[37], Token::Long);
        assert_eq!(tokens[38], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[39], Token::Register);
        assert_eq!(tokens[40], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[41], Token::Restrict);
        assert_eq!(tokens[42], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[43], Token::Return);
        assert_eq!(tokens[44], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[45], Token::Short);
        assert_eq!(tokens[46], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[47], Token::Signed);
        assert_eq!(tokens[48], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[49], Token::Sizeof);
        assert_eq!(tokens[50], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[51], Token::Static);
        assert_eq!(tokens[52], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[53], Token::Struct);
        assert_eq!(tokens[54], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[55], Token::Switch);
        assert_eq!(tokens[56], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[57], Token::Typedef);
        assert_eq!(tokens[58], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[59], Token::Union);
        assert_eq!(tokens[60], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[61], Token::Unsigned);
        assert_eq!(tokens[62], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[63], Token::Void);
        assert_eq!(tokens[64], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[65], Token::Volatile);
        assert_eq!(tokens[66], Token::Identifier("foo".to_string()));
        assert_eq!(tokens[67], Token::While);
        assert_eq!(tokens[68], Token::Identifier("foo".to_string()));
    }
}

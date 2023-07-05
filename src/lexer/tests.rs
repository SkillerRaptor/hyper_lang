/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#![cfg(test)]

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

#[test]
fn test_00() {
    let text = "00 00";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("00".to_string()));
    assert_eq!(tokens[1], Token::Number("00".to_string()));
}

#[test]
fn test_11() {
    let text = "11 11";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("11".to_string()));
    assert_eq!(tokens[1], Token::Number("11".to_string()));
}

#[test]
fn test_22() {
    let text = "22 22";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("22".to_string()));
    assert_eq!(tokens[1], Token::Number("22".to_string()));
}

#[test]
fn test_33() {
    let text = "33 33";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("33".to_string()));
    assert_eq!(tokens[1], Token::Number("33".to_string()));
}

#[test]
fn test_44() {
    let text = "44 44";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("44".to_string()));
    assert_eq!(tokens[1], Token::Number("44".to_string()));
}

#[test]
fn test_55() {
    let text = "55 55";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("55".to_string()));
    assert_eq!(tokens[1], Token::Number("55".to_string()));
}

#[test]
fn test_66() {
    let text = "66 66";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("66".to_string()));
    assert_eq!(tokens[1], Token::Number("66".to_string()));
}

#[test]
fn test_77() {
    let text = "77 77";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("77".to_string()));
    assert_eq!(tokens[1], Token::Number("77".to_string()));
}

#[test]
fn test_88() {
    let text = "88 88";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("88".to_string()));
    assert_eq!(tokens[1], Token::Number("88".to_string()));
}

#[test]
fn test_99() {
    let text = "99 99";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("99".to_string()));
    assert_eq!(tokens[1], Token::Number("99".to_string()));
}

#[test]
fn test_01() {
    let text = "01 01";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("01".to_string()));
    assert_eq!(tokens[1], Token::Number("01".to_string()));
}

#[test]
fn test_02() {
    let text = "02 02";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("02".to_string()));
    assert_eq!(tokens[1], Token::Number("02".to_string()));
}

#[test]
fn test_03() {
    let text = "03 03";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("03".to_string()));
    assert_eq!(tokens[1], Token::Number("03".to_string()));
}

#[test]
fn test_04() {
    let text = "04 04";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("04".to_string()));
    assert_eq!(tokens[1], Token::Number("04".to_string()));
}

#[test]
fn test_05() {
    let text = "05 05";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("05".to_string()));
    assert_eq!(tokens[1], Token::Number("05".to_string()));
}

#[test]
fn test_06() {
    let text = "06 06";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("06".to_string()));
    assert_eq!(tokens[1], Token::Number("06".to_string()));
}

#[test]
fn test_07() {
    let text = "07 07";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("07".to_string()));
    assert_eq!(tokens[1], Token::Number("07".to_string()));
}

#[test]
#[should_panic]
fn test_08() {
    let text = "08 08";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("08".to_string()));
    assert_eq!(tokens[1], Token::Number("08".to_string()));
}

#[test]
#[should_panic]
fn test_09() {
    let text = "09 09";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("09".to_string()));
    assert_eq!(tokens[1], Token::Number("09".to_string()));
}

#[test]
fn test_0x00() {
    let text = "0x00 0x00";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x00".to_string()));
    assert_eq!(tokens[1], Token::Number("0x00".to_string()));
}

#[test]
fn test_0x11() {
    let text = "0x11 0x11";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x11".to_string()));
    assert_eq!(tokens[1], Token::Number("0x11".to_string()));
}

#[test]
fn test_0x22() {
    let text = "0x22 0x22";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x22".to_string()));
    assert_eq!(tokens[1], Token::Number("0x22".to_string()));
}

#[test]
fn test_0x33() {
    let text = "0x33 0x33";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x33".to_string()));
    assert_eq!(tokens[1], Token::Number("0x33".to_string()));
}

#[test]
fn test_0x44() {
    let text = "0x44 0x44";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x44".to_string()));
    assert_eq!(tokens[1], Token::Number("0x44".to_string()));
}

#[test]
fn test_0x55() {
    let text = "0x55 0x55";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x55".to_string()));
    assert_eq!(tokens[1], Token::Number("0x55".to_string()));
}

#[test]
fn test_0x66() {
    let text = "0x66 0x66";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x66".to_string()));
    assert_eq!(tokens[1], Token::Number("0x66".to_string()));
}

#[test]
fn test_0x77() {
    let text = "0x77 0x77";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x77".to_string()));
    assert_eq!(tokens[1], Token::Number("0x77".to_string()));
}

#[test]
fn test_0x88() {
    let text = "0x88 0x88";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x88".to_string()));
    assert_eq!(tokens[1], Token::Number("0x88".to_string()));
}

#[test]
fn test_0x99() {
    let text = "0x99 0x99";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0x99".to_string()));
    assert_eq!(tokens[1], Token::Number("0x99".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0xaA() {
    let text = "0xaA 0xaA";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xaA".to_string()));
    assert_eq!(tokens[1], Token::Number("0xaA".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0xbB() {
    let text = "0xbB 0xbB";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xbB".to_string()));
    assert_eq!(tokens[1], Token::Number("0xbB".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0xcC() {
    let text = "0xcC 0xcC";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xcC".to_string()));
    assert_eq!(tokens[1], Token::Number("0xcC".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0xdD() {
    let text = "0xdD 0xdD";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xdD".to_string()));
    assert_eq!(tokens[1], Token::Number("0xdD".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0xeE() {
    let text = "0xeE 0xeE";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xeE".to_string()));
    assert_eq!(tokens[1], Token::Number("0xeE".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0xfF() {
    let text = "0xfF 0xfF";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xfF".to_string()));
    assert_eq!(tokens[1], Token::Number("0xfF".to_string()));
}

#[test]
#[should_panic]
#[allow(non_snake_case)]
fn test_0xgG() {
    let text = "0xgG 0xgG";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xgG".to_string()));
    assert_eq!(tokens[1], Token::Number("0xgG".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X00() {
    let text = "0X00 0X00";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X00".to_string()));
    assert_eq!(tokens[1], Token::Number("0X00".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X11() {
    let text = "0X11 0X11";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X11".to_string()));
    assert_eq!(tokens[1], Token::Number("0X11".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X22() {
    let text = "0X22 0X22";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X22".to_string()));
    assert_eq!(tokens[1], Token::Number("0X22".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X33() {
    let text = "0X33 0X33";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X33".to_string()));
    assert_eq!(tokens[1], Token::Number("0X33".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X44() {
    let text = "0X44 0X44";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X44".to_string()));
    assert_eq!(tokens[1], Token::Number("0X44".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X55() {
    let text = "0X55 0X55";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X55".to_string()));
    assert_eq!(tokens[1], Token::Number("0X55".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X66() {
    let text = "0X66 0X66";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X66".to_string()));
    assert_eq!(tokens[1], Token::Number("0X66".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X77() {
    let text = "0X77 0X77";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X77".to_string()));
    assert_eq!(tokens[1], Token::Number("0X77".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X88() {
    let text = "0X88 0X88";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X88".to_string()));
    assert_eq!(tokens[1], Token::Number("0X88".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0X99() {
    let text = "0X99 0X99";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0X99".to_string()));
    assert_eq!(tokens[1], Token::Number("0X99".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0XaA() {
    let text = "0XaA 0XaA";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XaA".to_string()));
    assert_eq!(tokens[1], Token::Number("0XaA".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0XbB() {
    let text = "0XbB 0XbB";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XbB".to_string()));
    assert_eq!(tokens[1], Token::Number("0XbB".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0XcC() {
    let text = "0XcC 0XcC";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XcC".to_string()));
    assert_eq!(tokens[1], Token::Number("0XcC".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0XdD() {
    let text = "0XdD 0XdD";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XdD".to_string()));
    assert_eq!(tokens[1], Token::Number("0XdD".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0XeE() {
    let text = "0XeE 0XeE";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XeE".to_string()));
    assert_eq!(tokens[1], Token::Number("0XeE".to_string()));
}

#[test]
#[allow(non_snake_case)]
fn test_0XfF() {
    let text = "0XfF 0XfF";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XfF".to_string()));
    assert_eq!(tokens[1], Token::Number("0XfF".to_string()));
}

#[test]
#[should_panic]
#[allow(non_snake_case)]
fn test_0XgG() {
    let text = "0XgG 0XgG";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0XgG".to_string()));
    assert_eq!(tokens[1], Token::Number("0XgG".to_string()));
}

#[test]
fn test_numbers() {
    let text = "
    00
    11
    22
    33
    44
    55
    66
    77
    88
    99
    01
    02
    03
    04
    05
    06
    07
    0x00
    0x11
    0x22
    0x33
    0x44
    0x55
    0x66
    0x77
    0x88
    0x99
    0xaA
    0xbB
    0xcC
    0xdD
    0xeE
    0xfF
    0X00
    0X11
    0X22
    0X33
    0X44
    0X55
    0X66
    0X77
    0X88
    0X99
    0XaA
    0XbB
    0XcC
    0XdD
    0XeE
    0XfF
    00u
    11u
    22u
    33u
    44u
    55u
    66u
    77u
    88u
    99u
    01u
    02u
    03u
    04u
    05u
    06u
    07u
    0x00u
    0x11u
    0x22u
    0x33u
    0x44u
    0x55u
    0x66u
    0x77u
    0x88u
    0x99u
    0xaAu
    0xbBu
    0xcCu
    0xdDu
    0xeEu
    0xfFu
    0X00u
    0X11u
    0X22u
    0X33u
    0X44u
    0X55u
    0X66u
    0X77u
    0X88u
    0X99u
    0XaAu
    0XbBu
    0XcCu
    0XdDu
    0XeEu
    0XfFu
    00ul
    11ul
    22ul
    33ul
    44ul
    55ul
    66ul
    77ul
    88ul
    99ul
    01ul
    02ul
    03ul
    04ul
    05ul
    06ul
    07ul
    0x00ul
    0x11ul
    0x22ul
    0x33ul
    0x44ul
    0x55ul
    0x66ul
    0x77ul
    0x88ul
    0x99ul
    0xaAul
    0xbBul
    0xcCul
    0xdDul
    0xeEul
    0xfFul
    0X00ul
    0X11ul
    0X22ul
    0X33ul
    0X44ul
    0X55ul
    0X66ul
    0X77ul
    0X88ul
    0X99ul
    0XaAul
    0XbBul
    0XcCul
    0XdDul
    0XeEul
    0XfFul
    00ull
    11ull
    22ull
    33ull
    44ull
    55ull
    66ull
    77ull
    88ull
    99ull
    01ull
    02ull
    03ull
    04ull
    05ull
    06ull
    07ull
    0x00ull
    0x11ull
    0x22ull
    0x33ull
    0x44ull
    0x55ull
    0x66ull
    0x77ull
    0x88ull
    0x99ull
    0xaAull
    0xbBull
    0xcCull
    0xdDull
    0xeEull
    0xfFull
    0X00ull
    0X11ull
    0X22ull
    0X33ull
    0X44ull
    0X55ull
    0X66ull
    0X77ull
    0X88ull
    0X99ull
    0XaAull
    0XbBull
    0XcCull
    0XdDull
    0XeEull
    0XfFull
    00U
    11U
    22U
    33U
    44U
    55U
    66U
    77U
    88U
    99U
    01U
    02U
    03U
    04U
    05U
    06U
    07U
    0x00U
    0x11U
    0x22U
    0x33U
    0x44U
    0x55U
    0x66U
    0x77U
    0x88U
    0x99U
    0xaAU
    0xbBU
    0xcCU
    0xdDU
    0xeEU
    0xfFU
    0X00U
    0X11U
    0X22U
    0X33U
    0X44U
    0X55U
    0X66U
    0X77U
    0X88U
    0X99U
    0XaAU
    0XbBU
    0XcCU
    0XdDU
    0XeEU
    0XfFU
    00UL
    11UL
    22UL
    33UL
    44UL
    55UL
    66UL
    77UL
    88UL
    99UL
    01UL
    02UL
    03UL
    04UL
    05UL
    06UL
    07UL
    0x00UL
    0x11UL
    0x22UL
    0x33UL
    0x44UL
    0x55UL
    0x66UL
    0x77UL
    0x88UL
    0x99UL
    0xaAUL
    0xbBUL
    0xcCUL
    0xdDUL
    0xeEUL
    0xfFUL
    0X00UL
    0X11UL
    0X22UL
    0X33UL
    0X44UL
    0X55UL
    0X66UL
    0X77UL
    0X88UL
    0X99UL
    0XaAUL
    0XbBUL
    0XcCUL
    0XdDUL
    0XeEUL
    0XfFUL
    00ULL
    11ULL
    22ULL
    33ULL
    44ULL
    55ULL
    66ULL
    77ULL
    88ULL
    99ULL
    01ULL
    02ULL
    03ULL
    04ULL
    05ULL
    06ULL
    07ULL
    0x00ULL
    0x11ULL
    0x22ULL
    0x33ULL
    0x44ULL
    0x55ULL
    0x66ULL
    0x77ULL
    0x88ULL
    0x99ULL
    0xaAULL
    0xbBULL
    0xcCULL
    0xdDULL
    0xeEULL
    0xfFULL
    0X00ULL
    0X11ULL
    0X22ULL
    0X33ULL
    0X44ULL
    0X55ULL
    0X66ULL
    0X77ULL
    0X88ULL
    0X99ULL
    0XaAULL
    0XbBULL
    0XcCULL
    0XdDULL
    0XeEULL
    0XfFULL
    00lu
    11lu
    22lu
    33lu
    44lu
    55lu
    66lu
    77lu
    88lu
    99lu
    01lu
    02lu
    03lu
    04lu
    05lu
    06lu
    07lu
    0x00lu
    0x11lu
    0x22lu
    0x33lu
    0x44lu
    0x55lu
    0x66lu
    0x77lu
    0x88lu
    0x99lu
    0xaAlu
    0xbBlu
    0xcClu
    0xdDlu
    0xeElu
    0xfFlu
    0X00lu
    0X11lu
    0X22lu
    0X33lu
    0X44lu
    0X55lu
    0X66lu
    0X77lu
    0X88lu
    0X99lu
    0XaAlu
    0XbBlu
    0XcClu
    0XdDlu
    0XeElu
    0XfFlu
    00llu
    11llu
    22llu
    33llu
    44llu
    55llu
    66llu
    77llu
    88llu
    99llu
    01llu
    02llu
    03llu
    04llu
    05llu
    06llu
    07llu
    0x00llu
    0x11llu
    0x22llu
    0x33llu
    0x44llu
    0x55llu
    0x66llu
    0x77llu
    0x88llu
    0x99llu
    0xaAllu
    0xbBllu
    0xcCllu
    0xdDllu
    0xeEllu
    0xfFllu
    0X00llu
    0X11llu
    0X22llu
    0X33llu
    0X44llu
    0X55llu
    0X66llu
    0X77llu
    0X88llu
    0X99llu
    0XaAllu
    0XbBllu
    0XcCllu
    0XdDllu
    0XeEllu
    0XfFllu
    00LU
    11LU
    22LU
    33LU
    44LU
    55LU
    66LU
    77LU
    88LU
    99LU
    01LU
    02LU
    03LU
    04LU
    05LU
    06LU
    07LU
    0x00LU
    0x11LU
    0x22LU
    0x33LU
    0x44LU
    0x55LU
    0x66LU
    0x77LU
    0x88LU
    0x99LU
    0xaALU
    0xbBLU
    0xcCLU
    0xdDLU
    0xeELU
    0xfFLU
    0X00LU
    0X11LU
    0X22LU
    0X33LU
    0X44LU
    0X55LU
    0X66LU
    0X77LU
    0X88LU
    0X99LU
    0XaALU
    0XbBLU
    0XcCLU
    0XdDLU
    0XeELU
    0XfFLU
    00LLU
    11LLU
    22LLU
    33LLU
    44LLU
    55LLU
    66LLU
    77LLU
    88LLU
    99LLU
    01LLU
    02LLU
    03LLU
    04LLU
    05LLU
    06LLU
    07LLU
    0x00LLU
    0x11LLU
    0x22LLU
    0x33LLU
    0x44LLU
    0x55LLU
    0x66LLU
    0x77LLU
    0x88LLU
    0x99LLU
    0xaALLU
    0xbBLLU
    0xcCLLU
    0xdDLLU
    0xeELLU
    0xfFLLU
    0X00LLU
    0X11LLU
    0X22LLU
    0X33LLU
    0X44LLU
    0X55LLU
    0X66LLU
    0X77LLU
    0X88LLU
    0X99LLU
    0XaALLU
    0XbBLLU
    0XcCLLU
    0XdDLLU
    0XeELLU
    0XfFLLU
    ";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 539);
    assert_eq!(tokens[0], Token::Number("00".to_string()));
    assert_eq!(tokens[1], Token::Number("11".to_string()));
    assert_eq!(tokens[2], Token::Number("22".to_string()));
    assert_eq!(tokens[3], Token::Number("33".to_string()));
    assert_eq!(tokens[4], Token::Number("44".to_string()));
    assert_eq!(tokens[5], Token::Number("55".to_string()));
    assert_eq!(tokens[6], Token::Number("66".to_string()));
    assert_eq!(tokens[7], Token::Number("77".to_string()));
    assert_eq!(tokens[8], Token::Number("88".to_string()));
    assert_eq!(tokens[9], Token::Number("99".to_string()));
    assert_eq!(tokens[10], Token::Number("01".to_string()));
    assert_eq!(tokens[11], Token::Number("02".to_string()));
    assert_eq!(tokens[12], Token::Number("03".to_string()));
    assert_eq!(tokens[13], Token::Number("04".to_string()));
    assert_eq!(tokens[14], Token::Number("05".to_string()));
    assert_eq!(tokens[15], Token::Number("06".to_string()));
    assert_eq!(tokens[16], Token::Number("07".to_string()));
    assert_eq!(tokens[17], Token::Number("0x00".to_string()));
    assert_eq!(tokens[18], Token::Number("0x11".to_string()));
    assert_eq!(tokens[19], Token::Number("0x22".to_string()));
    assert_eq!(tokens[20], Token::Number("0x33".to_string()));
    assert_eq!(tokens[21], Token::Number("0x44".to_string()));
    assert_eq!(tokens[22], Token::Number("0x55".to_string()));
    assert_eq!(tokens[23], Token::Number("0x66".to_string()));
    assert_eq!(tokens[24], Token::Number("0x77".to_string()));
    assert_eq!(tokens[25], Token::Number("0x88".to_string()));
    assert_eq!(tokens[26], Token::Number("0x99".to_string()));
    assert_eq!(tokens[27], Token::Number("0xaA".to_string()));
    assert_eq!(tokens[28], Token::Number("0xbB".to_string()));
    assert_eq!(tokens[29], Token::Number("0xcC".to_string()));
    assert_eq!(tokens[30], Token::Number("0xdD".to_string()));
    assert_eq!(tokens[31], Token::Number("0xeE".to_string()));
    assert_eq!(tokens[32], Token::Number("0xfF".to_string()));
    assert_eq!(tokens[33], Token::Number("0X00".to_string()));
    assert_eq!(tokens[34], Token::Number("0X11".to_string()));
    assert_eq!(tokens[35], Token::Number("0X22".to_string()));
    assert_eq!(tokens[36], Token::Number("0X33".to_string()));
    assert_eq!(tokens[37], Token::Number("0X44".to_string()));
    assert_eq!(tokens[38], Token::Number("0X55".to_string()));
    assert_eq!(tokens[39], Token::Number("0X66".to_string()));
    assert_eq!(tokens[40], Token::Number("0X77".to_string()));
    assert_eq!(tokens[41], Token::Number("0X88".to_string()));
    assert_eq!(tokens[42], Token::Number("0X99".to_string()));
    assert_eq!(tokens[43], Token::Number("0XaA".to_string()));
    assert_eq!(tokens[44], Token::Number("0XbB".to_string()));
    assert_eq!(tokens[45], Token::Number("0XcC".to_string()));
    assert_eq!(tokens[46], Token::Number("0XdD".to_string()));
    assert_eq!(tokens[47], Token::Number("0XeE".to_string()));
    assert_eq!(tokens[48], Token::Number("0XfF".to_string()));
    assert_eq!(tokens[49], Token::Number("00u".to_string()));
    assert_eq!(tokens[50], Token::Number("11u".to_string()));
    assert_eq!(tokens[51], Token::Number("22u".to_string()));
    assert_eq!(tokens[52], Token::Number("33u".to_string()));
    assert_eq!(tokens[53], Token::Number("44u".to_string()));
    assert_eq!(tokens[54], Token::Number("55u".to_string()));
    assert_eq!(tokens[55], Token::Number("66u".to_string()));
    assert_eq!(tokens[56], Token::Number("77u".to_string()));
    assert_eq!(tokens[57], Token::Number("88u".to_string()));
    assert_eq!(tokens[58], Token::Number("99u".to_string()));
    assert_eq!(tokens[59], Token::Number("01u".to_string()));
    assert_eq!(tokens[60], Token::Number("02u".to_string()));
    assert_eq!(tokens[61], Token::Number("03u".to_string()));
    assert_eq!(tokens[62], Token::Number("04u".to_string()));
    assert_eq!(tokens[63], Token::Number("05u".to_string()));
    assert_eq!(tokens[64], Token::Number("06u".to_string()));
    assert_eq!(tokens[65], Token::Number("07u".to_string()));
    assert_eq!(tokens[66], Token::Number("0x00u".to_string()));
    assert_eq!(tokens[67], Token::Number("0x11u".to_string()));
    assert_eq!(tokens[68], Token::Number("0x22u".to_string()));
    assert_eq!(tokens[69], Token::Number("0x33u".to_string()));
    assert_eq!(tokens[70], Token::Number("0x44u".to_string()));
    assert_eq!(tokens[71], Token::Number("0x55u".to_string()));
    assert_eq!(tokens[72], Token::Number("0x66u".to_string()));
    assert_eq!(tokens[73], Token::Number("0x77u".to_string()));
    assert_eq!(tokens[74], Token::Number("0x88u".to_string()));
    assert_eq!(tokens[75], Token::Number("0x99u".to_string()));
    assert_eq!(tokens[76], Token::Number("0xaAu".to_string()));
    assert_eq!(tokens[77], Token::Number("0xbBu".to_string()));
    assert_eq!(tokens[78], Token::Number("0xcCu".to_string()));
    assert_eq!(tokens[79], Token::Number("0xdDu".to_string()));
    assert_eq!(tokens[80], Token::Number("0xeEu".to_string()));
    assert_eq!(tokens[81], Token::Number("0xfFu".to_string()));
    assert_eq!(tokens[82], Token::Number("0X00u".to_string()));
    assert_eq!(tokens[83], Token::Number("0X11u".to_string()));
    assert_eq!(tokens[84], Token::Number("0X22u".to_string()));
    assert_eq!(tokens[85], Token::Number("0X33u".to_string()));
    assert_eq!(tokens[86], Token::Number("0X44u".to_string()));
    assert_eq!(tokens[87], Token::Number("0X55u".to_string()));
    assert_eq!(tokens[88], Token::Number("0X66u".to_string()));
    assert_eq!(tokens[89], Token::Number("0X77u".to_string()));
    assert_eq!(tokens[90], Token::Number("0X88u".to_string()));
    assert_eq!(tokens[91], Token::Number("0X99u".to_string()));
    assert_eq!(tokens[92], Token::Number("0XaAu".to_string()));
    assert_eq!(tokens[93], Token::Number("0XbBu".to_string()));
    assert_eq!(tokens[94], Token::Number("0XcCu".to_string()));
    assert_eq!(tokens[95], Token::Number("0XdDu".to_string()));
    assert_eq!(tokens[96], Token::Number("0XeEu".to_string()));
    assert_eq!(tokens[97], Token::Number("0XfFu".to_string()));
    assert_eq!(tokens[98], Token::Number("00ul".to_string()));
    assert_eq!(tokens[99], Token::Number("11ul".to_string()));
    assert_eq!(tokens[100], Token::Number("22ul".to_string()));
    assert_eq!(tokens[101], Token::Number("33ul".to_string()));
    assert_eq!(tokens[102], Token::Number("44ul".to_string()));
    assert_eq!(tokens[103], Token::Number("55ul".to_string()));
    assert_eq!(tokens[104], Token::Number("66ul".to_string()));
    assert_eq!(tokens[105], Token::Number("77ul".to_string()));
    assert_eq!(tokens[106], Token::Number("88ul".to_string()));
    assert_eq!(tokens[107], Token::Number("99ul".to_string()));
    assert_eq!(tokens[108], Token::Number("01ul".to_string()));
    assert_eq!(tokens[109], Token::Number("02ul".to_string()));
    assert_eq!(tokens[110], Token::Number("03ul".to_string()));
    assert_eq!(tokens[111], Token::Number("04ul".to_string()));
    assert_eq!(tokens[112], Token::Number("05ul".to_string()));
    assert_eq!(tokens[113], Token::Number("06ul".to_string()));
    assert_eq!(tokens[114], Token::Number("07ul".to_string()));
    assert_eq!(tokens[115], Token::Number("0x00ul".to_string()));
    assert_eq!(tokens[116], Token::Number("0x11ul".to_string()));
    assert_eq!(tokens[117], Token::Number("0x22ul".to_string()));
    assert_eq!(tokens[118], Token::Number("0x33ul".to_string()));
    assert_eq!(tokens[119], Token::Number("0x44ul".to_string()));
    assert_eq!(tokens[120], Token::Number("0x55ul".to_string()));
    assert_eq!(tokens[121], Token::Number("0x66ul".to_string()));
    assert_eq!(tokens[122], Token::Number("0x77ul".to_string()));
    assert_eq!(tokens[123], Token::Number("0x88ul".to_string()));
    assert_eq!(tokens[124], Token::Number("0x99ul".to_string()));
    assert_eq!(tokens[125], Token::Number("0xaAul".to_string()));
    assert_eq!(tokens[126], Token::Number("0xbBul".to_string()));
    assert_eq!(tokens[127], Token::Number("0xcCul".to_string()));
    assert_eq!(tokens[128], Token::Number("0xdDul".to_string()));
    assert_eq!(tokens[129], Token::Number("0xeEul".to_string()));
    assert_eq!(tokens[130], Token::Number("0xfFul".to_string()));
    assert_eq!(tokens[131], Token::Number("0X00ul".to_string()));
    assert_eq!(tokens[132], Token::Number("0X11ul".to_string()));
    assert_eq!(tokens[133], Token::Number("0X22ul".to_string()));
    assert_eq!(tokens[134], Token::Number("0X33ul".to_string()));
    assert_eq!(tokens[135], Token::Number("0X44ul".to_string()));
    assert_eq!(tokens[136], Token::Number("0X55ul".to_string()));
    assert_eq!(tokens[137], Token::Number("0X66ul".to_string()));
    assert_eq!(tokens[138], Token::Number("0X77ul".to_string()));
    assert_eq!(tokens[139], Token::Number("0X88ul".to_string()));
    assert_eq!(tokens[140], Token::Number("0X99ul".to_string()));
    assert_eq!(tokens[141], Token::Number("0XaAul".to_string()));
    assert_eq!(tokens[142], Token::Number("0XbBul".to_string()));
    assert_eq!(tokens[143], Token::Number("0XcCul".to_string()));
    assert_eq!(tokens[144], Token::Number("0XdDul".to_string()));
    assert_eq!(tokens[145], Token::Number("0XeEul".to_string()));
    assert_eq!(tokens[146], Token::Number("0XfFul".to_string()));
    assert_eq!(tokens[147], Token::Number("00ull".to_string()));
    assert_eq!(tokens[148], Token::Number("11ull".to_string()));
    assert_eq!(tokens[149], Token::Number("22ull".to_string()));
    assert_eq!(tokens[150], Token::Number("33ull".to_string()));
    assert_eq!(tokens[151], Token::Number("44ull".to_string()));
    assert_eq!(tokens[152], Token::Number("55ull".to_string()));
    assert_eq!(tokens[153], Token::Number("66ull".to_string()));
    assert_eq!(tokens[154], Token::Number("77ull".to_string()));
    assert_eq!(tokens[155], Token::Number("88ull".to_string()));
    assert_eq!(tokens[156], Token::Number("99ull".to_string()));
    assert_eq!(tokens[157], Token::Number("01ull".to_string()));
    assert_eq!(tokens[158], Token::Number("02ull".to_string()));
    assert_eq!(tokens[159], Token::Number("03ull".to_string()));
    assert_eq!(tokens[160], Token::Number("04ull".to_string()));
    assert_eq!(tokens[161], Token::Number("05ull".to_string()));
    assert_eq!(tokens[162], Token::Number("06ull".to_string()));
    assert_eq!(tokens[163], Token::Number("07ull".to_string()));
    assert_eq!(tokens[164], Token::Number("0x00ull".to_string()));
    assert_eq!(tokens[165], Token::Number("0x11ull".to_string()));
    assert_eq!(tokens[166], Token::Number("0x22ull".to_string()));
    assert_eq!(tokens[167], Token::Number("0x33ull".to_string()));
    assert_eq!(tokens[168], Token::Number("0x44ull".to_string()));
    assert_eq!(tokens[169], Token::Number("0x55ull".to_string()));
    assert_eq!(tokens[170], Token::Number("0x66ull".to_string()));
    assert_eq!(tokens[171], Token::Number("0x77ull".to_string()));
    assert_eq!(tokens[172], Token::Number("0x88ull".to_string()));
    assert_eq!(tokens[173], Token::Number("0x99ull".to_string()));
    assert_eq!(tokens[174], Token::Number("0xaAull".to_string()));
    assert_eq!(tokens[175], Token::Number("0xbBull".to_string()));
    assert_eq!(tokens[176], Token::Number("0xcCull".to_string()));
    assert_eq!(tokens[177], Token::Number("0xdDull".to_string()));
    assert_eq!(tokens[178], Token::Number("0xeEull".to_string()));
    assert_eq!(tokens[179], Token::Number("0xfFull".to_string()));
    assert_eq!(tokens[180], Token::Number("0X00ull".to_string()));
    assert_eq!(tokens[181], Token::Number("0X11ull".to_string()));
    assert_eq!(tokens[182], Token::Number("0X22ull".to_string()));
    assert_eq!(tokens[183], Token::Number("0X33ull".to_string()));
    assert_eq!(tokens[184], Token::Number("0X44ull".to_string()));
    assert_eq!(tokens[185], Token::Number("0X55ull".to_string()));
    assert_eq!(tokens[186], Token::Number("0X66ull".to_string()));
    assert_eq!(tokens[187], Token::Number("0X77ull".to_string()));
    assert_eq!(tokens[188], Token::Number("0X88ull".to_string()));
    assert_eq!(tokens[189], Token::Number("0X99ull".to_string()));
    assert_eq!(tokens[190], Token::Number("0XaAull".to_string()));
    assert_eq!(tokens[191], Token::Number("0XbBull".to_string()));
    assert_eq!(tokens[192], Token::Number("0XcCull".to_string()));
    assert_eq!(tokens[193], Token::Number("0XdDull".to_string()));
    assert_eq!(tokens[194], Token::Number("0XeEull".to_string()));
    assert_eq!(tokens[195], Token::Number("0XfFull".to_string()));
    assert_eq!(tokens[196], Token::Number("00U".to_string()));
    assert_eq!(tokens[197], Token::Number("11U".to_string()));
    assert_eq!(tokens[198], Token::Number("22U".to_string()));
    assert_eq!(tokens[199], Token::Number("33U".to_string()));
    assert_eq!(tokens[200], Token::Number("44U".to_string()));
    assert_eq!(tokens[201], Token::Number("55U".to_string()));
    assert_eq!(tokens[202], Token::Number("66U".to_string()));
    assert_eq!(tokens[203], Token::Number("77U".to_string()));
    assert_eq!(tokens[204], Token::Number("88U".to_string()));
    assert_eq!(tokens[205], Token::Number("99U".to_string()));
    assert_eq!(tokens[206], Token::Number("01U".to_string()));
    assert_eq!(tokens[207], Token::Number("02U".to_string()));
    assert_eq!(tokens[208], Token::Number("03U".to_string()));
    assert_eq!(tokens[209], Token::Number("04U".to_string()));
    assert_eq!(tokens[210], Token::Number("05U".to_string()));
    assert_eq!(tokens[211], Token::Number("06U".to_string()));
    assert_eq!(tokens[212], Token::Number("07U".to_string()));
    assert_eq!(tokens[213], Token::Number("0x00U".to_string()));
    assert_eq!(tokens[214], Token::Number("0x11U".to_string()));
    assert_eq!(tokens[215], Token::Number("0x22U".to_string()));
    assert_eq!(tokens[216], Token::Number("0x33U".to_string()));
    assert_eq!(tokens[217], Token::Number("0x44U".to_string()));
    assert_eq!(tokens[218], Token::Number("0x55U".to_string()));
    assert_eq!(tokens[219], Token::Number("0x66U".to_string()));
    assert_eq!(tokens[220], Token::Number("0x77U".to_string()));
    assert_eq!(tokens[221], Token::Number("0x88U".to_string()));
    assert_eq!(tokens[222], Token::Number("0x99U".to_string()));
    assert_eq!(tokens[223], Token::Number("0xaAU".to_string()));
    assert_eq!(tokens[224], Token::Number("0xbBU".to_string()));
    assert_eq!(tokens[225], Token::Number("0xcCU".to_string()));
    assert_eq!(tokens[226], Token::Number("0xdDU".to_string()));
    assert_eq!(tokens[227], Token::Number("0xeEU".to_string()));
    assert_eq!(tokens[228], Token::Number("0xfFU".to_string()));
    assert_eq!(tokens[229], Token::Number("0X00U".to_string()));
    assert_eq!(tokens[230], Token::Number("0X11U".to_string()));
    assert_eq!(tokens[231], Token::Number("0X22U".to_string()));
    assert_eq!(tokens[232], Token::Number("0X33U".to_string()));
    assert_eq!(tokens[233], Token::Number("0X44U".to_string()));
    assert_eq!(tokens[234], Token::Number("0X55U".to_string()));
    assert_eq!(tokens[235], Token::Number("0X66U".to_string()));
    assert_eq!(tokens[236], Token::Number("0X77U".to_string()));
    assert_eq!(tokens[237], Token::Number("0X88U".to_string()));
    assert_eq!(tokens[238], Token::Number("0X99U".to_string()));
    assert_eq!(tokens[239], Token::Number("0XaAU".to_string()));
    assert_eq!(tokens[240], Token::Number("0XbBU".to_string()));
    assert_eq!(tokens[241], Token::Number("0XcCU".to_string()));
    assert_eq!(tokens[242], Token::Number("0XdDU".to_string()));
    assert_eq!(tokens[243], Token::Number("0XeEU".to_string()));
    assert_eq!(tokens[244], Token::Number("0XfFU".to_string()));
    assert_eq!(tokens[245], Token::Number("00UL".to_string()));
    assert_eq!(tokens[246], Token::Number("11UL".to_string()));
    assert_eq!(tokens[247], Token::Number("22UL".to_string()));
    assert_eq!(tokens[248], Token::Number("33UL".to_string()));
    assert_eq!(tokens[249], Token::Number("44UL".to_string()));
    assert_eq!(tokens[250], Token::Number("55UL".to_string()));
    assert_eq!(tokens[251], Token::Number("66UL".to_string()));
    assert_eq!(tokens[252], Token::Number("77UL".to_string()));
    assert_eq!(tokens[253], Token::Number("88UL".to_string()));
    assert_eq!(tokens[254], Token::Number("99UL".to_string()));
    assert_eq!(tokens[255], Token::Number("01UL".to_string()));
    assert_eq!(tokens[256], Token::Number("02UL".to_string()));
    assert_eq!(tokens[257], Token::Number("03UL".to_string()));
    assert_eq!(tokens[258], Token::Number("04UL".to_string()));
    assert_eq!(tokens[259], Token::Number("05UL".to_string()));
    assert_eq!(tokens[260], Token::Number("06UL".to_string()));
    assert_eq!(tokens[261], Token::Number("07UL".to_string()));
    assert_eq!(tokens[262], Token::Number("0x00UL".to_string()));
    assert_eq!(tokens[263], Token::Number("0x11UL".to_string()));
    assert_eq!(tokens[264], Token::Number("0x22UL".to_string()));
    assert_eq!(tokens[265], Token::Number("0x33UL".to_string()));
    assert_eq!(tokens[266], Token::Number("0x44UL".to_string()));
    assert_eq!(tokens[267], Token::Number("0x55UL".to_string()));
    assert_eq!(tokens[268], Token::Number("0x66UL".to_string()));
    assert_eq!(tokens[269], Token::Number("0x77UL".to_string()));
    assert_eq!(tokens[270], Token::Number("0x88UL".to_string()));
    assert_eq!(tokens[271], Token::Number("0x99UL".to_string()));
    assert_eq!(tokens[272], Token::Number("0xaAUL".to_string()));
    assert_eq!(tokens[273], Token::Number("0xbBUL".to_string()));
    assert_eq!(tokens[274], Token::Number("0xcCUL".to_string()));
    assert_eq!(tokens[275], Token::Number("0xdDUL".to_string()));
    assert_eq!(tokens[276], Token::Number("0xeEUL".to_string()));
    assert_eq!(tokens[277], Token::Number("0xfFUL".to_string()));
    assert_eq!(tokens[278], Token::Number("0X00UL".to_string()));
    assert_eq!(tokens[279], Token::Number("0X11UL".to_string()));
    assert_eq!(tokens[280], Token::Number("0X22UL".to_string()));
    assert_eq!(tokens[281], Token::Number("0X33UL".to_string()));
    assert_eq!(tokens[282], Token::Number("0X44UL".to_string()));
    assert_eq!(tokens[283], Token::Number("0X55UL".to_string()));
    assert_eq!(tokens[284], Token::Number("0X66UL".to_string()));
    assert_eq!(tokens[285], Token::Number("0X77UL".to_string()));
    assert_eq!(tokens[286], Token::Number("0X88UL".to_string()));
    assert_eq!(tokens[287], Token::Number("0X99UL".to_string()));
    assert_eq!(tokens[288], Token::Number("0XaAUL".to_string()));
    assert_eq!(tokens[289], Token::Number("0XbBUL".to_string()));
    assert_eq!(tokens[290], Token::Number("0XcCUL".to_string()));
    assert_eq!(tokens[291], Token::Number("0XdDUL".to_string()));
    assert_eq!(tokens[292], Token::Number("0XeEUL".to_string()));
    assert_eq!(tokens[293], Token::Number("0XfFUL".to_string()));
    assert_eq!(tokens[294], Token::Number("00ULL".to_string()));
    assert_eq!(tokens[295], Token::Number("11ULL".to_string()));
    assert_eq!(tokens[296], Token::Number("22ULL".to_string()));
    assert_eq!(tokens[297], Token::Number("33ULL".to_string()));
    assert_eq!(tokens[298], Token::Number("44ULL".to_string()));
    assert_eq!(tokens[299], Token::Number("55ULL".to_string()));
    assert_eq!(tokens[300], Token::Number("66ULL".to_string()));
    assert_eq!(tokens[301], Token::Number("77ULL".to_string()));
    assert_eq!(tokens[302], Token::Number("88ULL".to_string()));
    assert_eq!(tokens[303], Token::Number("99ULL".to_string()));
    assert_eq!(tokens[304], Token::Number("01ULL".to_string()));
    assert_eq!(tokens[305], Token::Number("02ULL".to_string()));
    assert_eq!(tokens[306], Token::Number("03ULL".to_string()));
    assert_eq!(tokens[307], Token::Number("04ULL".to_string()));
    assert_eq!(tokens[308], Token::Number("05ULL".to_string()));
    assert_eq!(tokens[309], Token::Number("06ULL".to_string()));
    assert_eq!(tokens[310], Token::Number("07ULL".to_string()));
    assert_eq!(tokens[311], Token::Number("0x00ULL".to_string()));
    assert_eq!(tokens[312], Token::Number("0x11ULL".to_string()));
    assert_eq!(tokens[313], Token::Number("0x22ULL".to_string()));
    assert_eq!(tokens[314], Token::Number("0x33ULL".to_string()));
    assert_eq!(tokens[315], Token::Number("0x44ULL".to_string()));
    assert_eq!(tokens[316], Token::Number("0x55ULL".to_string()));
    assert_eq!(tokens[317], Token::Number("0x66ULL".to_string()));
    assert_eq!(tokens[318], Token::Number("0x77ULL".to_string()));
    assert_eq!(tokens[319], Token::Number("0x88ULL".to_string()));
    assert_eq!(tokens[320], Token::Number("0x99ULL".to_string()));
    assert_eq!(tokens[321], Token::Number("0xaAULL".to_string()));
    assert_eq!(tokens[322], Token::Number("0xbBULL".to_string()));
    assert_eq!(tokens[323], Token::Number("0xcCULL".to_string()));
    assert_eq!(tokens[324], Token::Number("0xdDULL".to_string()));
    assert_eq!(tokens[325], Token::Number("0xeEULL".to_string()));
    assert_eq!(tokens[326], Token::Number("0xfFULL".to_string()));
    assert_eq!(tokens[327], Token::Number("0X00ULL".to_string()));
    assert_eq!(tokens[328], Token::Number("0X11ULL".to_string()));
    assert_eq!(tokens[329], Token::Number("0X22ULL".to_string()));
    assert_eq!(tokens[330], Token::Number("0X33ULL".to_string()));
    assert_eq!(tokens[331], Token::Number("0X44ULL".to_string()));
    assert_eq!(tokens[332], Token::Number("0X55ULL".to_string()));
    assert_eq!(tokens[333], Token::Number("0X66ULL".to_string()));
    assert_eq!(tokens[334], Token::Number("0X77ULL".to_string()));
    assert_eq!(tokens[335], Token::Number("0X88ULL".to_string()));
    assert_eq!(tokens[336], Token::Number("0X99ULL".to_string()));
    assert_eq!(tokens[337], Token::Number("0XaAULL".to_string()));
    assert_eq!(tokens[338], Token::Number("0XbBULL".to_string()));
    assert_eq!(tokens[339], Token::Number("0XcCULL".to_string()));
    assert_eq!(tokens[340], Token::Number("0XdDULL".to_string()));
    assert_eq!(tokens[341], Token::Number("0XeEULL".to_string()));
    assert_eq!(tokens[342], Token::Number("0XfFULL".to_string()));
    assert_eq!(tokens[343], Token::Number("00lu".to_string()));
    assert_eq!(tokens[344], Token::Number("11lu".to_string()));
    assert_eq!(tokens[345], Token::Number("22lu".to_string()));
    assert_eq!(tokens[346], Token::Number("33lu".to_string()));
    assert_eq!(tokens[347], Token::Number("44lu".to_string()));
    assert_eq!(tokens[348], Token::Number("55lu".to_string()));
    assert_eq!(tokens[349], Token::Number("66lu".to_string()));
    assert_eq!(tokens[350], Token::Number("77lu".to_string()));
    assert_eq!(tokens[351], Token::Number("88lu".to_string()));
    assert_eq!(tokens[352], Token::Number("99lu".to_string()));
    assert_eq!(tokens[353], Token::Number("01lu".to_string()));
    assert_eq!(tokens[354], Token::Number("02lu".to_string()));
    assert_eq!(tokens[355], Token::Number("03lu".to_string()));
    assert_eq!(tokens[356], Token::Number("04lu".to_string()));
    assert_eq!(tokens[357], Token::Number("05lu".to_string()));
    assert_eq!(tokens[358], Token::Number("06lu".to_string()));
    assert_eq!(tokens[359], Token::Number("07lu".to_string()));
    assert_eq!(tokens[360], Token::Number("0x00lu".to_string()));
    assert_eq!(tokens[361], Token::Number("0x11lu".to_string()));
    assert_eq!(tokens[362], Token::Number("0x22lu".to_string()));
    assert_eq!(tokens[363], Token::Number("0x33lu".to_string()));
    assert_eq!(tokens[364], Token::Number("0x44lu".to_string()));
    assert_eq!(tokens[365], Token::Number("0x55lu".to_string()));
    assert_eq!(tokens[366], Token::Number("0x66lu".to_string()));
    assert_eq!(tokens[367], Token::Number("0x77lu".to_string()));
    assert_eq!(tokens[368], Token::Number("0x88lu".to_string()));
    assert_eq!(tokens[369], Token::Number("0x99lu".to_string()));
    assert_eq!(tokens[370], Token::Number("0xaAlu".to_string()));
    assert_eq!(tokens[371], Token::Number("0xbBlu".to_string()));
    assert_eq!(tokens[372], Token::Number("0xcClu".to_string()));
    assert_eq!(tokens[373], Token::Number("0xdDlu".to_string()));
    assert_eq!(tokens[374], Token::Number("0xeElu".to_string()));
    assert_eq!(tokens[375], Token::Number("0xfFlu".to_string()));
    assert_eq!(tokens[376], Token::Number("0X00lu".to_string()));
    assert_eq!(tokens[377], Token::Number("0X11lu".to_string()));
    assert_eq!(tokens[378], Token::Number("0X22lu".to_string()));
    assert_eq!(tokens[379], Token::Number("0X33lu".to_string()));
    assert_eq!(tokens[380], Token::Number("0X44lu".to_string()));
    assert_eq!(tokens[381], Token::Number("0X55lu".to_string()));
    assert_eq!(tokens[382], Token::Number("0X66lu".to_string()));
    assert_eq!(tokens[383], Token::Number("0X77lu".to_string()));
    assert_eq!(tokens[384], Token::Number("0X88lu".to_string()));
    assert_eq!(tokens[385], Token::Number("0X99lu".to_string()));
    assert_eq!(tokens[386], Token::Number("0XaAlu".to_string()));
    assert_eq!(tokens[387], Token::Number("0XbBlu".to_string()));
    assert_eq!(tokens[388], Token::Number("0XcClu".to_string()));
    assert_eq!(tokens[389], Token::Number("0XdDlu".to_string()));
    assert_eq!(tokens[390], Token::Number("0XeElu".to_string()));
    assert_eq!(tokens[391], Token::Number("0XfFlu".to_string()));
    assert_eq!(tokens[392], Token::Number("00llu".to_string()));
    assert_eq!(tokens[393], Token::Number("11llu".to_string()));
    assert_eq!(tokens[394], Token::Number("22llu".to_string()));
    assert_eq!(tokens[395], Token::Number("33llu".to_string()));
    assert_eq!(tokens[396], Token::Number("44llu".to_string()));
    assert_eq!(tokens[397], Token::Number("55llu".to_string()));
    assert_eq!(tokens[398], Token::Number("66llu".to_string()));
    assert_eq!(tokens[399], Token::Number("77llu".to_string()));
    assert_eq!(tokens[400], Token::Number("88llu".to_string()));
    assert_eq!(tokens[401], Token::Number("99llu".to_string()));
    assert_eq!(tokens[402], Token::Number("01llu".to_string()));
    assert_eq!(tokens[403], Token::Number("02llu".to_string()));
    assert_eq!(tokens[404], Token::Number("03llu".to_string()));
    assert_eq!(tokens[405], Token::Number("04llu".to_string()));
    assert_eq!(tokens[406], Token::Number("05llu".to_string()));
    assert_eq!(tokens[407], Token::Number("06llu".to_string()));
    assert_eq!(tokens[408], Token::Number("07llu".to_string()));
    assert_eq!(tokens[409], Token::Number("0x00llu".to_string()));
    assert_eq!(tokens[410], Token::Number("0x11llu".to_string()));
    assert_eq!(tokens[411], Token::Number("0x22llu".to_string()));
    assert_eq!(tokens[412], Token::Number("0x33llu".to_string()));
    assert_eq!(tokens[413], Token::Number("0x44llu".to_string()));
    assert_eq!(tokens[414], Token::Number("0x55llu".to_string()));
    assert_eq!(tokens[415], Token::Number("0x66llu".to_string()));
    assert_eq!(tokens[416], Token::Number("0x77llu".to_string()));
    assert_eq!(tokens[417], Token::Number("0x88llu".to_string()));
    assert_eq!(tokens[418], Token::Number("0x99llu".to_string()));
    assert_eq!(tokens[419], Token::Number("0xaAllu".to_string()));
    assert_eq!(tokens[420], Token::Number("0xbBllu".to_string()));
    assert_eq!(tokens[421], Token::Number("0xcCllu".to_string()));
    assert_eq!(tokens[422], Token::Number("0xdDllu".to_string()));
    assert_eq!(tokens[423], Token::Number("0xeEllu".to_string()));
    assert_eq!(tokens[424], Token::Number("0xfFllu".to_string()));
    assert_eq!(tokens[425], Token::Number("0X00llu".to_string()));
    assert_eq!(tokens[426], Token::Number("0X11llu".to_string()));
    assert_eq!(tokens[427], Token::Number("0X22llu".to_string()));
    assert_eq!(tokens[428], Token::Number("0X33llu".to_string()));
    assert_eq!(tokens[429], Token::Number("0X44llu".to_string()));
    assert_eq!(tokens[430], Token::Number("0X55llu".to_string()));
    assert_eq!(tokens[431], Token::Number("0X66llu".to_string()));
    assert_eq!(tokens[432], Token::Number("0X77llu".to_string()));
    assert_eq!(tokens[433], Token::Number("0X88llu".to_string()));
    assert_eq!(tokens[434], Token::Number("0X99llu".to_string()));
    assert_eq!(tokens[435], Token::Number("0XaAllu".to_string()));
    assert_eq!(tokens[436], Token::Number("0XbBllu".to_string()));
    assert_eq!(tokens[437], Token::Number("0XcCllu".to_string()));
    assert_eq!(tokens[438], Token::Number("0XdDllu".to_string()));
    assert_eq!(tokens[439], Token::Number("0XeEllu".to_string()));
    assert_eq!(tokens[440], Token::Number("0XfFllu".to_string()));
    assert_eq!(tokens[441], Token::Number("00LU".to_string()));
    assert_eq!(tokens[442], Token::Number("11LU".to_string()));
    assert_eq!(tokens[443], Token::Number("22LU".to_string()));
    assert_eq!(tokens[444], Token::Number("33LU".to_string()));
    assert_eq!(tokens[445], Token::Number("44LU".to_string()));
    assert_eq!(tokens[446], Token::Number("55LU".to_string()));
    assert_eq!(tokens[447], Token::Number("66LU".to_string()));
    assert_eq!(tokens[448], Token::Number("77LU".to_string()));
    assert_eq!(tokens[449], Token::Number("88LU".to_string()));
    assert_eq!(tokens[450], Token::Number("99LU".to_string()));
    assert_eq!(tokens[451], Token::Number("01LU".to_string()));
    assert_eq!(tokens[452], Token::Number("02LU".to_string()));
    assert_eq!(tokens[453], Token::Number("03LU".to_string()));
    assert_eq!(tokens[454], Token::Number("04LU".to_string()));
    assert_eq!(tokens[455], Token::Number("05LU".to_string()));
    assert_eq!(tokens[456], Token::Number("06LU".to_string()));
    assert_eq!(tokens[457], Token::Number("07LU".to_string()));
    assert_eq!(tokens[458], Token::Number("0x00LU".to_string()));
    assert_eq!(tokens[459], Token::Number("0x11LU".to_string()));
    assert_eq!(tokens[460], Token::Number("0x22LU".to_string()));
    assert_eq!(tokens[461], Token::Number("0x33LU".to_string()));
    assert_eq!(tokens[462], Token::Number("0x44LU".to_string()));
    assert_eq!(tokens[463], Token::Number("0x55LU".to_string()));
    assert_eq!(tokens[464], Token::Number("0x66LU".to_string()));
    assert_eq!(tokens[465], Token::Number("0x77LU".to_string()));
    assert_eq!(tokens[466], Token::Number("0x88LU".to_string()));
    assert_eq!(tokens[467], Token::Number("0x99LU".to_string()));
    assert_eq!(tokens[468], Token::Number("0xaALU".to_string()));
    assert_eq!(tokens[469], Token::Number("0xbBLU".to_string()));
    assert_eq!(tokens[470], Token::Number("0xcCLU".to_string()));
    assert_eq!(tokens[471], Token::Number("0xdDLU".to_string()));
    assert_eq!(tokens[472], Token::Number("0xeELU".to_string()));
    assert_eq!(tokens[473], Token::Number("0xfFLU".to_string()));
    assert_eq!(tokens[474], Token::Number("0X00LU".to_string()));
    assert_eq!(tokens[475], Token::Number("0X11LU".to_string()));
    assert_eq!(tokens[476], Token::Number("0X22LU".to_string()));
    assert_eq!(tokens[477], Token::Number("0X33LU".to_string()));
    assert_eq!(tokens[478], Token::Number("0X44LU".to_string()));
    assert_eq!(tokens[479], Token::Number("0X55LU".to_string()));
    assert_eq!(tokens[480], Token::Number("0X66LU".to_string()));
    assert_eq!(tokens[481], Token::Number("0X77LU".to_string()));
    assert_eq!(tokens[482], Token::Number("0X88LU".to_string()));
    assert_eq!(tokens[483], Token::Number("0X99LU".to_string()));
    assert_eq!(tokens[484], Token::Number("0XaALU".to_string()));
    assert_eq!(tokens[485], Token::Number("0XbBLU".to_string()));
    assert_eq!(tokens[486], Token::Number("0XcCLU".to_string()));
    assert_eq!(tokens[487], Token::Number("0XdDLU".to_string()));
    assert_eq!(tokens[488], Token::Number("0XeELU".to_string()));
    assert_eq!(tokens[489], Token::Number("0XfFLU".to_string()));
    assert_eq!(tokens[490], Token::Number("00LLU".to_string()));
    assert_eq!(tokens[491], Token::Number("11LLU".to_string()));
    assert_eq!(tokens[492], Token::Number("22LLU".to_string()));
    assert_eq!(tokens[493], Token::Number("33LLU".to_string()));
    assert_eq!(tokens[494], Token::Number("44LLU".to_string()));
    assert_eq!(tokens[495], Token::Number("55LLU".to_string()));
    assert_eq!(tokens[496], Token::Number("66LLU".to_string()));
    assert_eq!(tokens[497], Token::Number("77LLU".to_string()));
    assert_eq!(tokens[498], Token::Number("88LLU".to_string()));
    assert_eq!(tokens[499], Token::Number("99LLU".to_string()));
    assert_eq!(tokens[500], Token::Number("01LLU".to_string()));
    assert_eq!(tokens[501], Token::Number("02LLU".to_string()));
    assert_eq!(tokens[502], Token::Number("03LLU".to_string()));
    assert_eq!(tokens[503], Token::Number("04LLU".to_string()));
    assert_eq!(tokens[504], Token::Number("05LLU".to_string()));
    assert_eq!(tokens[505], Token::Number("06LLU".to_string()));
    assert_eq!(tokens[506], Token::Number("07LLU".to_string()));
    assert_eq!(tokens[507], Token::Number("0x00LLU".to_string()));
    assert_eq!(tokens[508], Token::Number("0x11LLU".to_string()));
    assert_eq!(tokens[509], Token::Number("0x22LLU".to_string()));
    assert_eq!(tokens[510], Token::Number("0x33LLU".to_string()));
    assert_eq!(tokens[511], Token::Number("0x44LLU".to_string()));
    assert_eq!(tokens[512], Token::Number("0x55LLU".to_string()));
    assert_eq!(tokens[513], Token::Number("0x66LLU".to_string()));
    assert_eq!(tokens[514], Token::Number("0x77LLU".to_string()));
    assert_eq!(tokens[515], Token::Number("0x88LLU".to_string()));
    assert_eq!(tokens[516], Token::Number("0x99LLU".to_string()));
    assert_eq!(tokens[517], Token::Number("0xaALLU".to_string()));
    assert_eq!(tokens[518], Token::Number("0xbBLLU".to_string()));
    assert_eq!(tokens[519], Token::Number("0xcCLLU".to_string()));
    assert_eq!(tokens[520], Token::Number("0xdDLLU".to_string()));
    assert_eq!(tokens[521], Token::Number("0xeELLU".to_string()));
    assert_eq!(tokens[522], Token::Number("0xfFLLU".to_string()));
    assert_eq!(tokens[523], Token::Number("0X00LLU".to_string()));
    assert_eq!(tokens[524], Token::Number("0X11LLU".to_string()));
    assert_eq!(tokens[525], Token::Number("0X22LLU".to_string()));
    assert_eq!(tokens[526], Token::Number("0X33LLU".to_string()));
    assert_eq!(tokens[527], Token::Number("0X44LLU".to_string()));
    assert_eq!(tokens[528], Token::Number("0X55LLU".to_string()));
    assert_eq!(tokens[529], Token::Number("0X66LLU".to_string()));
    assert_eq!(tokens[530], Token::Number("0X77LLU".to_string()));
    assert_eq!(tokens[531], Token::Number("0X88LLU".to_string()));
    assert_eq!(tokens[532], Token::Number("0X99LLU".to_string()));
    assert_eq!(tokens[533], Token::Number("0XaALLU".to_string()));
    assert_eq!(tokens[534], Token::Number("0XbBLLU".to_string()));
    assert_eq!(tokens[535], Token::Number("0XcCLLU".to_string()));
    assert_eq!(tokens[536], Token::Number("0XdDLLU".to_string()));
    assert_eq!(tokens[537], Token::Number("0XeELLU".to_string()));
    assert_eq!(tokens[538], Token::Number("0XfFLLU".to_string()));
}

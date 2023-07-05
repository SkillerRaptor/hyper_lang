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
    ";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 49);
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
}

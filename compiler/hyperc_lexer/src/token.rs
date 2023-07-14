/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use hyperc_span::Span;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BinaryOperation {
    Plus,
    Minus,

    Star,
    Slash,

    Percent,

    Caret,
    And,
    Or,

    LeftShift,
    RightShift,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Delimiter {
    Parenthesis,
    Bracket,
    Brace,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LiteralKind {
    Number,
    Character,
    String,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Keyword {
    None,
    Auto,
    Break,
    Case,
    Char,
    Const,
    Continue,
    Default,
    Do,
    Double,
    Else,
    Enum,
    Extern,
    Float,
    For,
    Goto,
    If,
    Inline,
    Int,
    Long,
    Register,
    Restrict,
    Return,
    Short,
    Signed,
    Sizeof,
    Static,
    Struct,
    Switch,
    Typedef,
    Union,
    Unsigned,
    Void,
    Volatile,
    While,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TokenKind {
    Eof,

    OpenDelimiter(Delimiter),
    CloseDelimiter(Delimiter),

    BinaryOperation(BinaryOperation),
    BinaryOperationEqual(BinaryOperation),

    Period,
    Arrow,
    Increment,
    Decrement,
    Tilde,
    ExclamationMark,
    LessThan,
    GreaterThan,
    LessThanOrEqual,
    GreaterThanOrEqual,
    Equal,
    NotEqual,
    QuestionMark,
    Colon,
    Semicolon,
    Ellipsis,
    Assign,
    Comma,
    LogicalAnd,
    LogicalOr,
    PoundSign,
    DoublePoundSign,

    Identifier(Keyword),

    Literal(LiteralKind),
}

#[derive(Clone, Debug)]
pub struct Token {
    kind: TokenKind,
    span: Span,
}

impl Token {
    pub fn new(kind: TokenKind, span: Span) -> Self {
        Self { kind, span }
    }

    pub fn kind(&self) -> &TokenKind {
        &self.kind
    }

    pub fn span(&self) -> Span {
        self.span
    }
}

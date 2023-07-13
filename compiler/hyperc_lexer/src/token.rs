/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use hyperc_span::Span;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TokenKind {
    Eof,

    // Keywords
    /// auto
    Auto,
    /// break
    Break,
    /// case
    Case,
    /// char
    Char,
    /// const
    Const,
    /// continue
    Continue,
    /// default
    Default,
    /// do
    Do,
    /// double
    Double,
    /// else
    Else,
    /// enum
    Enum,
    /// extern
    Extern,
    /// float
    Float,
    /// for
    For,
    /// goto
    Goto,
    /// if
    If,
    /// inline
    Inline,
    /// int
    Int,
    /// long
    Long,
    /// register
    Register,
    /// restrict
    Restrict,
    /// return
    Return,
    /// short
    Short,
    /// signed
    Signed,
    /// sizeof
    Sizeof,
    /// static
    Static,
    /// struct
    Struct,
    /// switch
    Switch,
    /// typedef
    Typedef,
    /// union
    Union,
    /// unsigned
    Unsigned,
    /// void
    Void,
    /// volatile
    Volatile,
    /// while
    While,

    // Punctuators
    /// [
    BracketLeft,
    /// ]
    BracketRight,
    /// (
    ParenthesisLeft,
    /// )
    ParenthesisRight,
    /// {
    BraceLeft,
    /// }
    BraceRight,
    /// .
    Period,
    /// ->
    Arrow,
    /// ++
    Increment,
    /// --
    Decrement,
    /// &
    Ampersand,
    /// *
    Asterisk,
    /// +
    Plus,
    /// -
    Minus,
    /// ~
    Tilde,
    /// !
    ExclamationMark,
    /// /
    Slash,
    /// %
    Percent,
    /// <<
    LeftShift,
    /// >>
    RightShift,
    /// <
    LessThan,
    /// >
    GreaterThan,
    /// <=
    LessThanOrEqual,
    /// >=
    GreaterThanOrEqual,
    /// ==
    Equal,
    /// !=
    NotEqual,
    /// ^
    Caret,
    /// |
    Pipe,
    /// &&
    LogicalAnd,
    /// ||
    LogicalOr,
    /// ?
    QuestionMark,
    /// :
    Colon,
    /// ;
    Semicolon,
    /// ...
    Ellipsis,
    /// =
    Assign,
    /// *=
    MultiplyAssign,
    /// /=
    DivideAssign,
    /// %=
    ModuloAssign,
    /// +=
    PlusAssign,
    /// -=
    MinusAssign,
    /// <<=
    LeftShiftAssign,
    /// >>=
    RightShiftAssign,
    /// &=
    BitwiseAndAssign,
    /// ^=
    BitwiseXorAssign,
    /// |=
    BitwiseOrAssign,
    /// ,
    Comma,
    /// #
    PoundSign,
    /// ##
    DoublePoundSign,

    Identifier,
    Number,
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

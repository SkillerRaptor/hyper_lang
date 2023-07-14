/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use std::fmt::{self, Display, Formatter};

#[derive(Clone, Debug)]
pub enum ErrorCode {
    E0001(String),
    E0002,
    E0003,
}

impl ErrorCode {
    pub fn code(&self) -> &'static str {
        match *self {
            ErrorCode::E0001(_) => "E0001",
            ErrorCode::E0002 => "E0002",
            ErrorCode::E0003 => "E0003",
        }
    }
}

impl Display for ErrorCode {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match *self {
            ErrorCode::E0001(ref token) => write!(f, "unexpected token, found `{}`", token),
            ErrorCode::E0002 => write!(f, "unclosed hexadecimal number"),
            ErrorCode::E0003 => write!(f, "unclosed string literal"),
        }
    }
}

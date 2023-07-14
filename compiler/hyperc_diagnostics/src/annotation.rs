/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use hyperc_span::Span;

#[derive(Clone, Copy, Debug)]
pub enum Style {
    Primary,
    Secondary,
}

#[derive(Clone, Debug)]
pub struct Annotation {
    style: Style,
    span: Span,
    message: String,
}

impl Annotation {
    pub fn new(style: Style, span: Span, message: impl ToString) -> Self {
        Self {
            style,
            span,
            message: message.to_string(),
        }
    }

    pub fn primary(span: Span, message: impl ToString) -> Self {
        Self::new(Style::Primary, span, message)
    }

    pub fn secondary(span: Span, message: impl ToString) -> Self {
        Self::new(Style::Secondary, span, message)
    }

    pub fn style(&self) -> Style {
        self.style
    }

    pub fn span(&self) -> Span {
        self.span
    }

    pub fn message(&self) -> &str {
        &self.message
    }
}

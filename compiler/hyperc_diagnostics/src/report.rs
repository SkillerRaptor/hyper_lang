/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

use crate::{annotation::Annotation, errors::ErrorCode};

#[derive(Clone, Copy, Debug)]
pub enum Severity {
    Info,
    Warning,
    Error,
}

#[derive(Clone, Debug)]
pub struct Report {
    pub(crate) severity: Severity,
    pub(crate) message: Option<String>,
    pub(crate) code: Option<String>,
    pub(crate) annotations: Vec<Annotation>,
}

impl Report {
    pub fn new(severity: Severity) -> Self {
        Self {
            severity,
            message: None,
            code: None,
            annotations: Vec::new(),
        }
    }

    pub fn info() -> Self {
        Self::new(Severity::Info)
    }

    pub fn warning() -> Self {
        Self::new(Severity::Warning)
    }

    pub fn error() -> Self {
        Self::new(Severity::Error)
    }

    pub fn with_message(mut self, message: impl ToString) -> Self {
        self.message = Some(message.to_string());
        self.code = None;
        self
    }

    pub fn with_error_code(mut self, error_code: ErrorCode) -> Self {
        self.code = Some(error_code.code().to_string());
        self.message = Some(format!("{}", error_code));
        self
    }

    pub fn with_annotations(mut self, annotations: Vec<Annotation>) -> Self {
        self.annotations = annotations;
        self
    }
}

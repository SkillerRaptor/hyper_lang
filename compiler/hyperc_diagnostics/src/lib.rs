/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

pub mod annotation;
pub mod errors;
pub mod report;

use crate::{
    annotation::Style,
    report::{Report, Severity},
};

use codespan_reporting::{
    diagnostic::{self, LabelStyle},
    files::SimpleFiles,
    term::{
        self,
        termcolor::{ColorChoice, StandardStream},
        Config,
    },
};

#[derive(Debug)]
pub struct Diagnostic {
    files: SimpleFiles<String, String>,
    file_id: usize,
}

impl Diagnostic {
    pub fn new(file: impl ToString, source: impl ToString) -> Self {
        let mut files = SimpleFiles::new();
        let file_id = files.add(file.to_string(), source.to_string());

        Self { files, file_id }
    }

    pub fn report(&self, report: Report) {
        let Report {
            severity,
            message,
            code,
            annotations,
        } = report;

        let severity = match severity {
            Severity::Note => diagnostic::Severity::Note,
            Severity::Warning => diagnostic::Severity::Warning,
            Severity::Error => diagnostic::Severity::Error,
        };

        let mut diagnostic = diagnostic::Diagnostic::new(severity)
            .with_message(message.unwrap())
            .with_labels(
                annotations
                    .iter()
                    .map(|annotation| {
                        let style = match annotation.style() {
                            Style::Primary => LabelStyle::Primary,
                            Style::Secondary => LabelStyle::Secondary,
                        };
                        diagnostic::Label::new(
                            style,
                            self.file_id,
                            annotation.span().start()..annotation.span().end(),
                        )
                        .with_message(annotation.message())
                    })
                    .collect(),
            );

        if code.is_some() {
            diagnostic = diagnostic.with_code(code.unwrap());
        }

        let writer = StandardStream::stderr(ColorChoice::Always);
        let config = Config {
            ..Default::default()
        };

        term::emit(&mut writer.lock(), &config, &self.files, &diagnostic).unwrap();
    }
}

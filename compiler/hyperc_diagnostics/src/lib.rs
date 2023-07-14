/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

pub mod annotation;
pub mod errors;
pub mod report;

use annotate_snippets::{
    display_list::{DisplayList, FormatOptions},
    snippet::{self, AnnotationType, Slice, Snippet, SourceAnnotation},
};

use crate::{
    annotation::Style,
    report::{Report, Severity},
};

#[derive(Debug)]
pub struct Diagnostic {
    file: String,
    source: String,
}

impl Diagnostic {
    pub fn new(file: impl ToString, source: impl ToString) -> Self {
        Self {
            file: file.to_string(),
            source: source.to_string(),
        }
    }

    pub fn report(&self, report: Report) {
        let Report {
            severity,
            message,
            code,
            annotations,
        } = report;

        let annotation_type = match severity {
            Severity::Info => AnnotationType::Info,
            Severity::Warning => AnnotationType::Warning,
            Severity::Error => AnnotationType::Error,
        };

        let annotations = annotations
            .iter()
            .map(|annotation| SourceAnnotation {
                range: (annotation.span().start(), annotation.span().end()),
                label: annotation.message(),
                annotation_type: match annotation.style() {
                    Style::Primary => AnnotationType::Error,
                    Style::Secondary => AnnotationType::Info,
                },
            })
            .collect();

        let message = message.unwrap();

        let code = code.unwrap_or(String::new());

        let snippet = Snippet {
            title: Some(snippet::Annotation {
                id: if code.is_empty() {
                    None
                } else {
                    Some(code.as_str())
                },
                label: Some(message.as_str()),
                annotation_type,
            }),
            footer: vec![],
            slices: vec![Slice {
                source: &self.source,
                line_start: 1,
                origin: Some(self.file.as_str()),
                annotations,
                fold: true,
            }],
            opt: FormatOptions {
                color: true,
                ..Default::default()
            },
        };

        let display_list = DisplayList::from(snippet);
        println!("{}", display_list);
    }
}

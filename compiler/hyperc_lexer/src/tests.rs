/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

#![cfg(test)]

use super::*;

use paste::paste;
use rand::distributions::{Alphanumeric, DistString};

macro_rules! count {
    () => (0 as usize);
    ( $x:tt $($xs:tt)* ) => (1 as usize + count!($($xs)*));
}

macro_rules! test_keywords {
    ( $(($keyword:ident, $token:expr)),* $(,)? ) => {
        $(
            paste! {
                #[test]
                fn [<token_ $keyword>]() {
                    let text = concat!(stringify!($keyword), " ", stringify!($keyword));

                    let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
                    let mut lexer = Lexer::new(&diagnostic, text);
                    let tokens = lexer.lex().unwrap();

                    assert_eq!(tokens.len(), 2);
                    assert_eq!(tokens[0].kind(), $token);
                    assert_eq!(tokens[1].kind(), $token);
                }
            }
        )*

        #[test]
        fn token_keywords() {
            let text = concat!(
                $(
                    stringify!($keyword),
                    " ",
                )*
            );

            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
            let mut lexer = Lexer::new(&diagnostic, text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), count!($($keyword)*));

            let mut i = -1i32;
            $(
                i += 1;
                assert_eq!(tokens[i as usize].kind(), $token);
            )*
        }
    };
}

test_keywords! {
    (auto, TokenKind::Identifier(Keyword::Auto)),
    (break, TokenKind::Identifier(Keyword::Break)),
    (case, TokenKind::Identifier(Keyword::Case)),
    (char, TokenKind::Identifier(Keyword::Char)),
    (const, TokenKind::Identifier(Keyword::Const)),
    (continue, TokenKind::Identifier(Keyword::Continue)),
    (default, TokenKind::Identifier(Keyword::Default)),
    (do, TokenKind::Identifier(Keyword::Do)),
    (double, TokenKind::Identifier(Keyword::Double)),
    (else, TokenKind::Identifier(Keyword::Else)),
    (enum, TokenKind::Identifier(Keyword::Enum)),
    (extern, TokenKind::Identifier(Keyword::Extern)),
    (float, TokenKind::Identifier(Keyword::Float)),
    (for, TokenKind::Identifier(Keyword::For)),
    (goto, TokenKind::Identifier(Keyword::Goto)),
    (if, TokenKind::Identifier(Keyword::If)),
    (inline, TokenKind::Identifier(Keyword::Inline)),
    (int, TokenKind::Identifier(Keyword::Int)),
    (long, TokenKind::Identifier(Keyword::Long)),
    (register, TokenKind::Identifier(Keyword::Register)),
    (restrict, TokenKind::Identifier(Keyword::Restrict)),
    (return, TokenKind::Identifier(Keyword::Return)),
    (short, TokenKind::Identifier(Keyword::Short)),
    (signed, TokenKind::Identifier(Keyword::Signed)),
    (sizeof, TokenKind::Identifier(Keyword::Sizeof)),
    (static, TokenKind::Identifier(Keyword::Static)),
    (struct, TokenKind::Identifier(Keyword::Struct)),
    (switch, TokenKind::Identifier(Keyword::Switch)),
    (typedef, TokenKind::Identifier(Keyword::Typedef)),
    (union, TokenKind::Identifier(Keyword::Union)),
    (unsigned, TokenKind::Identifier(Keyword::Unsigned)),
    (void, TokenKind::Identifier(Keyword::Void)),
    (volatile, TokenKind::Identifier(Keyword::Volatile)),
    (while, TokenKind::Identifier(Keyword::While)),
}

macro_rules! test_punctuators {
    ( $(($name:ident, $punctuator:literal, $token:expr)),* $(,)? ) => {
        $(
            paste! {
                #[test]
                fn [<token_ $name>]() {
                    let text = concat!($punctuator, " ", $punctuator);

                    let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
                    let mut lexer = Lexer::new(&diagnostic, text);
                    let tokens = lexer.lex().unwrap();

                    assert_eq!(tokens.len(), 2);
                    assert_eq!(tokens[0].kind(), $token);
                    assert_eq!(
                        &text[tokens[0].span().start()..tokens[0].span().end()],
                        $punctuator
                    );
                    assert_eq!(tokens[1].kind(), $token);
                    assert_eq!(
                        &text[tokens[1].span().start()..tokens[1].span().end()],
                        $punctuator
                    );
                }
            }
        )*

        #[test]
        fn token_punctuators() {
            let text = concat!($($punctuator, " ", )*);

            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
            let mut lexer = Lexer::new(&diagnostic, text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), count!($($punctuator)*));

            let mut i = -1i32;
            $(
                i += 1;
                assert_eq!(tokens[i as usize].kind(), $token);
                assert_eq!(
                    &text[tokens[i as usize].span().start()..tokens[i as usize].span().end()],
                    $punctuator
                );
            )*
        }
    };
}

test_punctuators! {
    (bracket_left, "[", TokenKind::OpenDelimiter(Delimiter::Bracket)),
    (bracket_right, "]", TokenKind::CloseDelimiter(Delimiter::Bracket)),
    (parenthesis_left, "(", TokenKind::OpenDelimiter(Delimiter::Parenthesis)),
    (parenthesis_right, ")", TokenKind::CloseDelimiter(Delimiter::Parenthesis)),
    (brace_left, "{", TokenKind::OpenDelimiter(Delimiter::Brace)),
    (brace_right, "}", TokenKind::CloseDelimiter(Delimiter::Brace)),

    (plus, "+", TokenKind::BinaryOperation(BinaryOperation::Plus)),
    (minus, "-", TokenKind::BinaryOperation(BinaryOperation::Minus)),
    (asterisk, "*", TokenKind::BinaryOperation(BinaryOperation::Star)),
    (slash, "/", TokenKind::BinaryOperation(BinaryOperation::Slash)),
    (percent, "%", TokenKind::BinaryOperation(BinaryOperation::Percent)),
    (caret, "^", TokenKind::BinaryOperation(BinaryOperation::Caret)),
    (ampersand, "&", TokenKind::BinaryOperation(BinaryOperation::And)),
    (pipe, "|", TokenKind::BinaryOperation(BinaryOperation::Or)),
    (left_shift, "<<", TokenKind::BinaryOperation(BinaryOperation::LeftShift)),
    (right_shift, ">>", TokenKind::BinaryOperation(BinaryOperation::RightShift)),

    (plus_assign, "+=", TokenKind::BinaryOperationEqual(BinaryOperation::Plus)),
    (minus_assign, "-=", TokenKind::BinaryOperationEqual(BinaryOperation::Minus)),
    (multiply_assign, "*=", TokenKind::BinaryOperationEqual(BinaryOperation::Star)),
    (divide_assign, "/=", TokenKind::BinaryOperationEqual(BinaryOperation::Slash)),
    (modulo_assign, "%=", TokenKind::BinaryOperationEqual(BinaryOperation::Percent)),
    (bitwise_xor_assign, "^=", TokenKind::BinaryOperationEqual(BinaryOperation::Caret)),
    (bitwise_and_assign, "&=", TokenKind::BinaryOperationEqual(BinaryOperation::And)),
    (bitwise_or_assign, "|=", TokenKind::BinaryOperationEqual(BinaryOperation::Or)),
    (left_shift_assign, "<<=", TokenKind::BinaryOperationEqual(BinaryOperation::LeftShift)),
    (right_shift_assign, ">>=", TokenKind::BinaryOperationEqual(BinaryOperation::RightShift)),

    (period, ".", TokenKind::Period),
    (arrow, "->", TokenKind::Arrow),
    (increment, "++", TokenKind::Increment),
    (decrement, "--", TokenKind::Decrement),
    (tilde, "~", TokenKind::Tilde),
    (exclamation_nark, "!", TokenKind::ExclamationMark),
    (less_than, "<", TokenKind::LessThan),
    (greater_than, ">", TokenKind::GreaterThan),
    (less_than_or_equal, "<=", TokenKind::LessThanOrEqual),
    (greater_than_or_equal, ">=", TokenKind::GreaterThanOrEqual),
    (equal, "==", TokenKind::Equal),
    (not_equal, "!=", TokenKind::NotEqual),
    (logical_and, "&&", TokenKind::LogicalAnd),
    (logical_or, "||", TokenKind::LogicalOr),
    (question_mark, "?", TokenKind::QuestionMark),
    (colon, ":", TokenKind::Colon),
    (semicolon, ";", TokenKind::Semicolon),
    (ellipsis, "...", TokenKind::Ellipsis),
    (assign, "=", TokenKind::Assign),
    (comma, ",", TokenKind::Comma),
    (pound_sign, "#", TokenKind::PoundSign),
    (double_pound_sign, "##", TokenKind::DoublePoundSign),
}

#[test]
fn token_identifier() {
    for i in 1..100 {
        let string = Alphanumeric.sample_string(&mut rand::thread_rng(), i);

        if (string.as_bytes()[0] as char).is_ascii_digit() {
            continue;
        }

        let text = format!("{0} {0}", string);
        let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
        let mut lexer = Lexer::new(&diagnostic, text.as_str());
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0].kind(), TokenKind::Identifier(Keyword::None));
        assert_eq!(
            &text[tokens[0].span().start()..tokens[0].span().end()],
            string.as_str()
        );
        assert_eq!(tokens[1].kind(), TokenKind::Identifier(Keyword::None));
        assert_eq!(
            &text[tokens[1].span().start()..tokens[1].span().end()],
            string.as_str()
        );
    }
}

const INTEGER_SUFFIXES: [&str; 6] = ["u", "ul", "ull", "l", "lu", "llu"];

#[test]
fn test_decimal() {
    for i in 10..100 {
        let number = i.to_string();

        let text = format!("{number} {number}");
        let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
        let mut lexer = Lexer::new(&diagnostic, text.as_str());
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[0].span().start()..tokens[0].span().end()],
            number.as_str()
        );
        assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[1].span().start()..tokens[1].span().end()],
            number.as_str()
        );
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for i in 10..100 {
            let number = format!("{}{}", i, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for i in 10..100 {
            let number = format!("{}{}", i, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }
}

#[test]
fn test_octal() {
    for j in 0..7 {
        let number = format!("0{}", j);

        let text = format!("{number} {number}");
        let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
        let mut lexer = Lexer::new(&diagnostic, text.as_str());
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[0].span().start()..tokens[0].span().end()],
            number.as_str()
        );
        assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[1].span().start()..tokens[1].span().end()],
            number.as_str()
        );
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for j in 0..7 {
            let number = format!("0{}{}", j, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for j in 0..7 {
            let number = format!("0{}{}", j, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }
}

#[test]
#[should_panic]
fn test_octal_fail() {
    let text = "08 08";

    let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
    let mut lexer = Lexer::new(&diagnostic, text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
    assert_eq!(
        &text[tokens[0].span().start()..tokens[0].span().end()],
        "08"
    );
    assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
    assert_eq!(
        &text[tokens[1].span().start()..tokens[1].span().end()],
        "08"
    );
}

#[test]
fn test_hexadecimal_lower() {
    for i in 0..256 {
        let number = format!("{:#x}", i);

        let text = format!("{number} {number}");
        let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
        let mut lexer = Lexer::new(&diagnostic, text.as_str());
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[0].span().start()..tokens[0].span().end()],
            number.as_str()
        );
        assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[1].span().start()..tokens[1].span().end()],
            number.as_str()
        );
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for i in 0..256 {
            let number = format!("{:#x}{}", i, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for i in 0..256 {
            let number = format!("{:#x}{}", i, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }
}

#[test]
#[should_panic]
fn test_hexadecimal_lower_fail() {
    let text = "0xgg 0xgg";

    let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
    let mut lexer = Lexer::new(&diagnostic, text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
    assert_eq!(
        &text[tokens[0].span().start()..tokens[0].span().end()],
        "0xgg"
    );
    assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
    assert_eq!(
        &text[tokens[1].span().start()..tokens[1].span().end()],
        "0xgg"
    );
}

#[test]
fn test_hexadecimal_upper() {
    for i in 0..256 {
        let number = format!("{:#X}", i);

        let text = format!("{number} {number}");
        let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
        let mut lexer = Lexer::new(&diagnostic, text.as_str());
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[0].span().start()..tokens[0].span().end()],
            number.as_str()
        );
        assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            &text[tokens[1].span().start()..tokens[1].span().end()],
            number.as_str()
        );
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for i in 0..256 {
            let number = format!("{:#X}{}", i, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for i in 0..256 {
            let number = format!("{:#X}{}", i, suffix);

            let text = format!("{number} {number}");
            let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
            let mut lexer = Lexer::new(&diagnostic, text.as_str());
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[0].span().start()..tokens[0].span().end()],
                number.as_str()
            );
            assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
            assert_eq!(
                &text[tokens[1].span().start()..tokens[1].span().end()],
                number.as_str()
            );
        }
    }
}

#[test]
#[should_panic]
fn test_hexadecimal_upper_fail() {
    let text = "0xGG 0xGG";

    let diagnostic = Diagnostic::new("test.c", unindent::unindent(text));
    let mut lexer = Lexer::new(&diagnostic, text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0].kind(), TokenKind::Literal(LiteralKind::Number));
    assert_eq!(
        &text[tokens[0].span().start()..tokens[0].span().end()],
        "0xGG"
    );
    assert_eq!(tokens[1].kind(), TokenKind::Literal(LiteralKind::Number));
    assert_eq!(
        &text[tokens[1].span().start()..tokens[1].span().end()],
        "0xGG"
    );
}

#[test]
fn test_numbers() {
    let decimal = {
        let mut decimal = Vec::new();

        for i in 10..100 {
            let number = i.to_string();
            decimal.push(number);
        }

        for suffix_lower in INTEGER_SUFFIXES {
            let suffix = suffix_lower.to_ascii_lowercase();
            for i in 10..100 {
                let number = format!("{}{}", i, suffix);
                decimal.push(number);
            }
        }

        for suffix_upper in INTEGER_SUFFIXES {
            let suffix = suffix_upper.to_ascii_uppercase();
            for i in 10..100 {
                let number = format!("{}{}", i, suffix);
                decimal.push(number);
            }
        }

        decimal
    };

    let octal = {
        let mut octal = Vec::new();

        for j in 0..7 {
            let number = format!("0{}", j);
            octal.push(number);
        }

        for suffix_lower in INTEGER_SUFFIXES {
            let suffix = suffix_lower.to_ascii_lowercase();
            for j in 0..7 {
                let number = format!("0{}{}", j, suffix);
                octal.push(number);
            }
        }

        for suffix_upper in INTEGER_SUFFIXES {
            let suffix = suffix_upper.to_ascii_uppercase();
            for j in 0..7 {
                let number = format!("0{}{}", j, suffix);
                octal.push(number);
            }
        }

        octal
    };

    let hexadecimal_lower = {
        let mut hexadecimal_lower = Vec::new();

        for i in 0..256 {
            let number = format!("{:#x}", i);
            hexadecimal_lower.push(number);
        }

        for suffix_lower in INTEGER_SUFFIXES {
            let suffix = suffix_lower.to_ascii_lowercase();
            for i in 0..256 {
                let number = format!("{:#x}{}", i, suffix);
                hexadecimal_lower.push(number);
            }
        }

        for suffix_upper in INTEGER_SUFFIXES {
            let suffix = suffix_upper.to_ascii_uppercase();
            for i in 0..256 {
                let number = format!("{:#x}{}", i, suffix);
                hexadecimal_lower.push(number);
            }
        }

        hexadecimal_lower
    };

    let hexadecimal_upper = {
        let mut hexadecimal_upper = Vec::new();

        for i in 0..256 {
            let number = format!("{:#X}", i);
            hexadecimal_upper.push(number);
        }

        for suffix_lower in INTEGER_SUFFIXES {
            let suffix = suffix_lower.to_ascii_lowercase();
            for i in 0..256 {
                let number = format!("{:#X}{}", i, suffix);
                hexadecimal_upper.push(number);
            }
        }

        for suffix_upper in INTEGER_SUFFIXES {
            let suffix = suffix_upper.to_ascii_uppercase();
            for i in 0..256 {
                let number = format!("{:#X}{}", i, suffix);
                hexadecimal_upper.push(number);
            }
        }

        hexadecimal_upper
    };

    let text = format!(
        "{}\n{}\n{}\n{}",
        decimal.join("\n"),
        octal.join("\n"),
        hexadecimal_lower.join("\n"),
        hexadecimal_upper.join("\n")
    );

    let diagnostic = Diagnostic::new("test.c", unindent::unindent(text.as_str()));
    let mut lexer = Lexer::new(&diagnostic, text.as_str());
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 7917);

    let mut i = 0;
    for decimal in decimal {
        assert_eq!(tokens[i].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            text[tokens[i].span().start()..tokens[i].span().end()],
            decimal
        );
        i += 1;
    }

    for octal in octal {
        assert_eq!(tokens[i].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            text[tokens[i].span().start()..tokens[i].span().end()],
            octal
        );
        i += 1;
    }

    for hexadecimal_lower in hexadecimal_lower {
        assert_eq!(tokens[i].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            text[tokens[i].span().start()..tokens[i].span().end()],
            hexadecimal_lower
        );
        i += 1;
    }

    for hexadecimal_upper in hexadecimal_upper {
        assert_eq!(tokens[i].kind(), TokenKind::Literal(LiteralKind::Number));
        assert_eq!(
            text[tokens[i].span().start()..tokens[i].span().end()],
            hexadecimal_upper
        );
        i += 1;
    }
}

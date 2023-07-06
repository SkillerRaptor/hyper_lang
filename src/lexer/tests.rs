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

                    let mut lexer = Lexer::new(text);
                    let tokens = lexer.lex().unwrap();

                    assert_eq!(tokens.len(), 2);
                    assert_eq!(tokens[0], $token);
                    assert_eq!(tokens[1], $token);
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

            let mut lexer = Lexer::new(text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), count!($($keyword)*));

            let mut i = -1;
            $(
                i += 1;
                assert_eq!(tokens[i as usize], $token);
            )*
        }
    };
}

macro_rules! test_punctuators {
    ( $(($name:ident, $punctuator:literal, $token:expr)),* $(,)? ) => {
        $(
            paste! {
                #[test]
                fn [<token_ $name>]() {
                    let text = concat!($punctuator, " ", $punctuator);

                    let mut lexer = Lexer::new(text);
                    let tokens = lexer.lex().unwrap();

                    assert_eq!(tokens.len(), 2);
                    assert_eq!(tokens[0], $token);
                    assert_eq!(tokens[1], $token);
                }
            }
        )*

        #[test]
        fn token_punctuators() {
            let text = concat!($($punctuator, " ", )*);

            let mut lexer = Lexer::new(text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), count!($($punctuator)*));

            let mut i = -1;
            $(
                i += 1;
                assert_eq!(tokens[i as usize], $token);
            )*
        }
    };
}

test_keywords! {
    (auto, Token::Auto),
    (break, Token::Break),
    (case, Token::Case),
    (char, Token::Char),
    (const, Token::Const),
    (continue, Token::Continue),
    (default, Token::Default),
    (do, Token::Do),
    (double, Token::Double),
    (else, Token::Else),
    (enum, Token::Enum),
    (extern, Token::Extern),
    (float, Token::Float),
    (for, Token::For),
    (goto, Token::Goto),
    (if, Token::If),
    (inline, Token::Inline),
    (int, Token::Int),
    (long, Token::Long),
    (register, Token::Register),
    (restrict, Token::Restrict),
    (return, Token::Return),
    (short, Token::Short),
    (signed, Token::Signed),
    (sizeof, Token::Sizeof),
    (static, Token::Static),
    (struct, Token::Struct),
    (switch, Token::Switch),
    (typedef, Token::Typedef),
    (union, Token::Union),
    (unsigned, Token::Unsigned),
    (void, Token::Void),
    (volatile, Token::Volatile),
    (while, Token::While),
}

test_punctuators! {
    (bracket_left, "[", Token::BracketLeft),
    (bracket_right, "]", Token::BracketRight),
    (parenthesis_left, "(", Token::ParenthesisLeft),
    (parenthesis_right, ")", Token::ParenthesisRight),
    (brace_left, "{", Token::BraceLeft),
    (brace_right, "}", Token::BraceRight),
    (period, ".", Token::Period),
    (arrow, "->", Token::Arrow),
    (increment, "++", Token::Increment),
    (decrement, "--", Token::Decrement),
    (ampersand, "&", Token::Ampersand),
    (asterisk, "*", Token::Asterisk),
    (plus, "+", Token::Plus),
    (minus, "-", Token::Minus),
    (tilde, "~", Token::Tilde),
    (exclamation_nark, "!", Token::ExclamationMark),
    (slash, "/", Token::Slash),
    (percent, "%", Token::Percent),
    (left_shift, "<<", Token::LeftShift),
    (right_shift, ">>", Token::RightShift),
    (less_than, "<", Token::LessThan),
    (greater_than, ">", Token::GreaterThan),
    (less_than_or_equal, "<=", Token::LessThanOrEqual),
    (greater_than_or_equal, ">=", Token::GreaterThanOrEqual),
    (equal, "==", Token::Equal),
    (not_equal, "!=", Token::NotEqual),
    (caret, "^", Token::Caret),
    (pipe, "|", Token::Pipe),
    (logical_and, "&&", Token::LogicalAnd),
    (logical_or, "||", Token::LogicalOr),
    (question_mark, "?", Token::QuestionMark),
    (colon, ":", Token::Colon),
    (semicolon, ";", Token::Semicolon),
    (ellipsis, "...", Token::Ellipsis),
    (assign, "=", Token::Assign),
    (multiply_assign, "*=", Token::MultiplyAssign),
    (divide_assign, "/=", Token::DivideAssign),
    (modulo_assign, "%=", Token::ModuloAssign),
    (plus_assign, "+=", Token::PlusAssign),
    (minus_assign, "-=", Token::MinusAssign),
    (left_shift_assign, "<<=", Token::LeftShiftAssign),
    (right_shift_assign, ">>=", Token::RightShiftAssign),
    (bitwise_and_assign, "&=", Token::BitwiseAndAssign),
    (bitwise_xor_assign, "^=", Token::BitwiseXorAssign),
    (bitwise_or_assign, "|=", Token::BitwiseOrAssign),
    (comma, ",", Token::Comma),
    (pound_sign, "#", Token::PoundSign),
    (double_pound_sign, "##", Token::DoublePoundSign),
}

#[test]
fn token_identifier() {
    for i in 1..100 {
        let string = Alphanumeric.sample_string(&mut rand::thread_rng(), i);

        if (string.as_bytes()[0] as char).is_ascii_digit() {
            continue;
        }

        let text = format!("{0} {0}", string);
        let mut lexer = Lexer::new(&text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Identifier(string.clone()));
        assert_eq!(tokens[1], Token::Identifier(string));
    }
}

const INTEGER_SUFFIXES: [&str; 6] = ["u", "ul", "ull", "l", "lu", "llu"];

#[test]
fn test_decimal() {
    for i in 10..100 {
        let number = i.to_string();

        let text = format!("{number} {number}");
        let mut lexer = Lexer::new(&text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Number(number.clone()));
        assert_eq!(tokens[1], Token::Number(number));
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for i in 10..100 {
            let number = format!("{}{}", i, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for i in 10..100 {
            let number = format!("{}{}", i, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }
}

#[test]
fn test_octal() {
    for j in 0..7 {
        let number = format!("0{}", j);

        let text = format!("{number} {number}");
        let mut lexer = Lexer::new(&text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Number(number.clone()));
        assert_eq!(tokens[1], Token::Number(number));
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for j in 0..7 {
            let number = format!("0{}{}", j, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for j in 0..7 {
            let number = format!("0{}{}", j, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }
}

#[test]
#[should_panic]
fn test_octal_fail() {
    let text = "08 08";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("08".to_string()));
    assert_eq!(tokens[1], Token::Number("08".to_string()));
}

#[test]
fn test_hexadecimal_lower() {
    for i in 0..256 {
        let number = format!("{:#x}", i);

        let text = format!("{number} {number}");
        let mut lexer = Lexer::new(&text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Number(number.clone()));
        assert_eq!(tokens[1], Token::Number(number));
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for i in 0..256 {
            let number = format!("{:#x}{}", i, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for i in 0..256 {
            let number = format!("{:#x}{}", i, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }
}

#[test]
#[should_panic]
fn test_hexadecimal_lower_fail() {
    let text = "0xgg 0xgg";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xgg".to_string()));
    assert_eq!(tokens[1], Token::Number("0xgg".to_string()));
}

#[test]
fn test_hexadecimal_upper() {
    for i in 0..256 {
        let number = format!("{:#X}", i);

        let text = format!("{number} {number}");
        let mut lexer = Lexer::new(&text);
        let tokens = lexer.lex().unwrap();

        assert_eq!(tokens.len(), 2);
        assert_eq!(tokens[0], Token::Number(number.clone()));
        assert_eq!(tokens[1], Token::Number(number));
    }

    for suffix_lower in INTEGER_SUFFIXES {
        let suffix = suffix_lower.to_ascii_lowercase();
        for i in 0..256 {
            let number = format!("{:#X}{}", i, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }

    for suffix_upper in INTEGER_SUFFIXES {
        let suffix = suffix_upper.to_ascii_uppercase();
        for i in 0..256 {
            let number = format!("{:#X}{}", i, suffix);

            let text = format!("{number} {number}");
            let mut lexer = Lexer::new(&text);
            let tokens = lexer.lex().unwrap();

            assert_eq!(tokens.len(), 2);
            assert_eq!(tokens[0], Token::Number(number.clone()));
            assert_eq!(tokens[1], Token::Number(number));
        }
    }
}

#[test]
#[should_panic]
fn test_hexadecimal_upper_fail() {
    let text = "0xGG 0xGG";

    let mut lexer = Lexer::new(text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 2);
    assert_eq!(tokens[0], Token::Number("0xGG".to_string()));
    assert_eq!(tokens[1], Token::Number("0xGG".to_string()));
}

#[test]
fn test_numberss() {
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

    let mut lexer = Lexer::new(&text);
    let tokens = lexer.lex().unwrap();

    assert_eq!(tokens.len(), 7917);

    let mut i = 0;
    for decimal in decimal {
        assert_eq!(tokens[i], Token::Number(decimal));
        i += 1;
    }

    for octal in octal {
        assert_eq!(tokens[i], Token::Number(octal));
        i += 1;
    }

    for hexadecimal_lower in hexadecimal_lower {
        assert_eq!(tokens[i], Token::Number(hexadecimal_lower));
        i += 1;
    }

    for hexadecimal_upper in hexadecimal_upper {
        assert_eq!(tokens[i], Token::Number(hexadecimal_upper));
        i += 1;
    }
}

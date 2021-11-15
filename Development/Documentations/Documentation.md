# Hyper Documentation

## Contents
0. [Introduction](#introduction)
1. [Types](#types)
   1. [Primitive types](#primitive-types)
2. [Variables](#variables)
   1. [Mutable variables](#mutable-variables)
3. [Functions](#functions)
4. [Keywords](#keywords)

## Introduction
This documentation contains everything you need to know about the Hyper programming language.

## Types

### Primitive types
```hyper
bool

i8 i16 i32 i64
u8 u16 u32 u64

f32 f64

isize usize

char
string

void
```

## Variables
```hyper
let x: i8 = 5;
let y: i16 = -1;
let z: i16 = x - y;
```

### Mutable variables
```hyper
let x: mutable i8 = 5;
x = 6;
```

## Functions
```hyper
function add(x: i64, y: i64) -> i64
{
    return x + y;
}

function subtract(x: i64, y: i64) -> i64
{
    return x - y;
}
```

## Keywords
```hyper
else
for
function
if
let
mutable
return
while
```

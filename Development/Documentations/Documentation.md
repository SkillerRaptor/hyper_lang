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

## Types
### Primitive types
```hyper
bool

i8 i16 i32 i64
u8 u16 u32 u64

f32 f64

isize usize

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
let x: mut i8 = 5;
x = 6;
```

## Functions
```hyper
fn add(x: i64, y: i64) -> i64
{
    return x + y;
}

fn subtract(x: i64, y: i64) -> i64
{
    return x - y;
}
```

## Keywords
```hyper
else
for
fn
if
let
mut
return
while
```

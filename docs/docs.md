# Documentation

1. [Hyper Types](#hyper-types)
2. [Hyper Keywords](#hyper-keywords)
3. [Hyper Storage Types](#hyper-storage-types)
4. [Hyper Standard Packages](#hyper-standard-packages)

## Hyper Types

### Primitive Types

```hyper
bool

float double

int uint

void

nullptr
```

### Builtin Types

```hyper
 int8  int16  int32  int64
uint8 uint16 uint32 uint64

string
```

## Hyper Keywords

### Control

```hyper
break breakall continue

for do while of

if else

return
```

### Modules

```hyper
package

import export
```

### Storage Modifiers

```hyper
mutable static

virtual override
```

## Hyper Storage Types

### Enums

```hyper
enum my_enum
{
	first_value,
	second_value
}
```

### Structs

```hyper
struct my_struct
{
	some_data: uint64;
}
```

### Unions

```hyper
union my_union
{
	big: uint64;
	(
		small_a: uint32,
		small_b: uint32
	);
}
```

## Hyper Standard Packages

| Packages |     Description     |
|:--------:|:-------------------:|
| array    | Array               |
| io       | Input & Output      |
| math     | Math related        |
| memory   | Memory manipulation |
| net      | Networking          |
| os       | Platform Specific   |
| string   | String              |
| vector   | Vector              |

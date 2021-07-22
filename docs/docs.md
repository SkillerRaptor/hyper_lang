# Documentation

1. [Hyper Types](#hyper-types)
2. [Hyper Keywords](#hyper-keywords)
3. [Hyper Storage](#hyper-storage)
4. [Hyper Standard Packages](#hyper-standard-packages)

## Hyper Types

### Primitive Types
```hyper
bool

float double

int uint

void
```

### Builtin Types
```hyper
 int8  int16  int32  int64
uint8 uint16 uint32 uint64

string
```

## Hyper Keywords
```hyper
break breakall continue

for do while

if else

import export

of

mutable

virtual override

return
```

## Hyper Storages

### Enum
```hyper
enum my_enum
{
    first_value,
    second_value
}
```

### Struct
```hyper
struct my_struct
{
    some_data: uint64
}
```

### Union
```hyper
union my_union
{
    big: uint64,
    (
        small_a: uint32,
        small_b: uint32
    )
}
```

## Hyper Standard Packages
| Packages |     Description     |
|:--------:|:-------------------:|
|    io    |     Input/Output    |
|   math   |     Math related    |
|  memory  | Memory manipulation |
|    net   |      Networking     |
|    os    |  Platform Specific  |
|  string  |        String       |
|  vector  |        Vector       |

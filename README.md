# The Hyper Programming Language

[![Build Linux](https://img.shields.io/github/workflow/status/SkillerRaptor/HyperLang/build-linux?style=flat&label=Build%20Linux&logo=github)](https://github.com/SkillerRaptor/HyperLang/blob/master/.github/workflows/build-linux.yml)
[![Build MacOS](https://img.shields.io/github/workflow/status/SkillerRaptor/HyperLang/build-macos?style=flat&label=Build%20MacOS&logo=github)](https://github.com/SkillerRaptor/HyperLang/blob/master/.github/workflows/build-macos.yml)
[![Build Windows](https://img.shields.io/github/workflow/status/SkillerRaptor/HyperLang/build-windows?style=flat&label=Build%20Windows&logo=github)](https://github.com/SkillerRaptor/HyperLang/blob/master/.github/workflows/build-windows.yml)
[![License](https://img.shields.io/badge/license-MIT-yellow?style=flat)](https://github.com/SkillerRaptor/HyperLang/blob/master/LICENSE)

Hyper is a type-safe programming language, which has a high level of safety.

This repository contains the source code for Hyper. <br />
Anyone is welcome to contribute or use the source from Hyper.

## Contents

- [Getting Started](#getting-started)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Building

1. Download the source code by using Git and cloning the repository, or
   downloading it as a zip.

```shell
git clone https://github.com/SkillerRaptor/HyperLang
cd HyperLang
```

2. Create a folder in which the CMake project files will be generated in.

```shell
mkdir build
cd build
```

3. Configure the project by using
   the <code><a href="https://github.com/SkillerRaptor/HyperLang/blob/master/CMakeLists.txt">
   CMakeLists.txt</a></code> inside of the root directory.

```shell
cmake .. -D CMAKE_BUILD_TYPE=Debug
```

4. Build the project using CMake

```shell
cmake --build .
```

5. Run the executable to check if everything was built successfully.

## Features

The following features from provides the necessary level of safety for Hyper:

- No uninitialized data
- No undefined behavior
- No global variables
- No variable shadowing
- Immutable variables by default

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change. Please make sure to update tests as
appropriate.

## License

HyperLang is distributed under
the [MIT](https://github.com/SkillerRaptor/HyperLang/blob/master/LICENSE)
license.

# The Hyper Programming Language

[![Build Linux](https://img.shields.io/github/workflow/status/SkillerRaptor/HyperLang/build-linux?style=flat&label=Build%20Linux&logo=github)](https://github.com/SkillerRaptor/HyperLang/blob/master/.github/workflows/build-linux.yml)
[![Build Windows](https://img.shields.io/github/workflow/status/SkillerRaptor/HyperLang/build-windows?style=flat&label=Build%20Windows&logo=github)](https://github.com/SkillerRaptor/HyperLang/blob/master/.github/workflows/build-windows.yml)
[![License](https://img.shields.io/badge/license-MIT-yellow?style=flat)](https://github.com/SkillerRaptor/HyperLang/blob/master/LICENSE)

The Hyper programming language wants to provide an easy and fast solution for async code.

This repository contains the source code for Hyper. <br />
Anyone is welcome to contribute or use the source from Hyper.

## Contents

- [Getting Started](#getting-started)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

### Building

1. Download the source code by using Git by cloning the repository, or
   downloading it as an archive file.

```shell
git clone https://github.com/SkillerRaptor/HyperLang
cd HyperLang
```

2. Create a folder for CMake to generate the project files.

```shell
mkdir build
cd build
```

3. Configure the project by using CMake.

```shell
cmake .. -D CMAKE_BUILD_TYPE=Release
```

4. Build the project with CMake.

```shell
cmake --build .
```

5. Run the compiler to check if everything was built successfully.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change. Please make sure to update tests as
appropriate.

## License

HyperLang is distributed under
the [MIT](https://github.com/SkillerRaptor/HyperLang/blob/master/LICENSE)
license.

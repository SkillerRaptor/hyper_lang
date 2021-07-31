# HyperLang
[![Build Linux](https://github.com/SkillerRaptor/HyperLang/workflows/build-linux/badge.svg)](https://github.com/SkillerRaptor/HyperLang/blob/master/.github/workflows/build-linux.yml)
[![License](https://img.shields.io/badge/license-MIT-yellow)](https://github.com/SkillerRaptor/HyperLang/blob/master/LICENSE)

## Prerequisites for Linux
- build-essential
- ccache
- cmake
- llvm-10-dev
- lld-10-dev

### Installing Linux Developer Tools
Across the different distros of Linux, there are different packages you'll need to install:
 
- Debian-based distributions:
```shell
$ sudo apt install build-essential ccache cmake llvm-10-dev lld-10-dev
```

- Arch distributions:
```shell
$ sudo pacman -Sy base-devel ccache cmake llvm lld
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Please make sure to update tests as appropriate.

## License
The HyperLang is distributed under the [MIT](https://github.com/SkillerRaptor/HyperLang/blob/master/LICENSE) license.

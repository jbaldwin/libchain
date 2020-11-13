# libchain - C++17 std::string utility chain belt

[![CI](https://github.com/jbaldwin/libchain/workflows/build/badge.svg)](https://github.com/jbaldwin/libchain/workflows/build/badge.svg)
[![Coverage Status](https://coveralls.io/repos/github/jbaldwin/libchain/badge.svg?branch=master)](https://coveralls.io/github/jbaldwin/libchain?branch=master)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/jbaldwin/libchain.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/jbaldwin/libchain/context:cpp)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/89a3474520bc4ee682f348c8b4b09cf8)](https://www.codacy.com/gh/jbaldwin/libchain/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jbaldwin/libchain&amp;utm_campaign=Badge_Grade)
[![language][badge.language]][language]
[![license][badge.license]][license]

https://github.com/jbaldwin/libchain

## Usage

### Requirements
    C++17 compiler (g++/clang++)
        Tested on g++-9 and clang++-9
    CMake
    make and/or ninja

### Instructions

#### Building
    mkdir Release && cd Release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

## Examples

```C++
    ${EXAMPLE_README_CPP}
````

## Support

File bug reports, feature requests and questions using [GitHub Issues](https://github.com/jbaldwin/libchain/issues)

## Readme updates
To edit this file the template is located at `.githooks/readme-template.md`, editing it directly in the root README.md will be overwritten by the `git pre-commit` hook which automatically replaces the code portions of this file with the appropriate examples.

## Code formatting
This library has a `git pre-commit` hook which is installed when `cmake` is invoked.  Any files that are commited will automatically have `clang-format` run on them before.

Copyright © 2020, Josh Baldwin

[badge.language]: https://img.shields.io/badge/language-C%2B%2B17-yellow.svg
[badge.license]: https://img.shields.io/badge/license-MIT-blue

[language]: https://en.wikipedia.org/wiki/C%2B%2B17
[license]: https://en.wikipedia.org/wiki/MIT_License

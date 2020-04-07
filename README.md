libchain - C++17 std::string utility chain belt.
================================================

[![CircleCI](https://circleci.com/gh/jbaldwin/libchain/tree/master.svg?style=svg)](https://circleci.com/gh/jbaldwin/libchain/tree/master)
[![language][badge.language]][language]
[![license][badge.license]][license]

[badge.language]: https://img.shields.io/badge/language-C%2B%2B17-yellow.svg
[badge.license]: https://img.shields.io/badge/license-MIT-blue

[language]: https://en.wikipedia.org/wiki/C%2B%2B17
[license]: https://en.wikipedia.org/wiki/MIT_License

https://github.com/jbaldwin/libchain

# Usage #

## Requirements
    C++17 compiler (g++/clang++)
    CMake
    make and/or ninja

## Instructions

### Building
    mkdir Release && cd Release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

# Examples

```C++
using namespace chain;

// A simple csv split. split() only allocates space for the std::string_view
// values that it returns, it does not make any copies of the input data.
auto parts = str::split("1,2,3", ',');
// parts = { "1", "2", "3" }

// A split mapped into integers.
auto parts = str::split_map<int64_t>("1,2,3", ',', [](auto part) {
    return str::to_number<int64_t>(part).value_or(0);
});
/// parts = { 1, 2, 3 }

// A pre-allocated split, for large splits to reduce allocations.
std::vector<std::string_view> parts{};
parts.reserve(128);
str::split("1,2,3,...,128", ',', parts);
// parts = { "1", "2", "3", ... , "128" }

// A simple csv join.
std::vector<int64_t> parts{1,2,3};
auto joined = str::join(parts, ',');
// joined == "1,2,3"

// A map join which squares its parts first.
std::vector<int64_t> parts{1,2,3};
auto joined = str::map_join(parts, ',', [](int64_t x) { return x * x; });
// joined == "1,4,9"

// Simple consistent to number api, leverages std::optional instead of exceptions.
auto value = str::to_number<uint64_t>("420").value_or(0);
// value == 420
````

## Support

File bug reports, feature requests and questions using [GitHub Issues](https://github.com/jbaldwin/libchain/issues)

Copyright © 2020, Josh Baldwin
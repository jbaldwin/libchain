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
    #include <iostream>

    #include <chain/chain.hpp>

    int main()
    {
        using namespace chain;

        auto print_parts = [](auto& parts) {
            for(const auto& part : parts) {
                std::cout << part << " ";
            }
            std::cout << "\n";
        };

        // A simple csv split. split() only allocates space for the std::string_view
        // values that it returns, it does not make any copies of the input data.
        auto parts1 = str::split("1,2,3", ',');
        // parts1 = { "1", "2", "3" }
        print_parts(parts1);

        // A split mapped into integers.
        auto parts2 = str::split_map<int64_t>("1,2,3", ',', [](std::string_view part) {
            return str::to_number<int64_t>(part).value_or(0);
        });
        /// parts2 = { 1, 2, 3 }
        print_parts(parts2);

        // A pre-allocated split, for large splits to reduce allocations.
        std::vector<std::string_view> parts3{};
        parts3.reserve(128);
        str::split("1,2,3,...,128", ',', parts3);
        // parts3 = { "1", "2", "3", ... , "128" }
        print_parts(parts3);

        // A simple csv join.
        std::vector<int64_t> parts4{1,2,3};
        auto joined1 = str::join(parts4, ',');
        // joined1 == "1,2,3"
        std::cout << joined1 << "\n";

        // A map join which squares its parts first.
        std::vector<int64_t> parts5{1,2,3};
        auto joined2 = str::map_join(parts5, ',', [](int64_t x) { return x * x; });
        // joined2 == "1,4,9"
        std::cout << joined2 << "\n";

        // Simple consistent to number api, leverages std::optional instead of exceptions.
        auto value = str::to_number<uint64_t>("420").value_or(0);
        // value == 420
        std::cout << value << "\n";

        return 0;
    }
````

## Support

File bug reports, feature requests and questions using [GitHub Issues](https://github.com/jbaldwin/libchain/issues)

Copyright © 2020, Josh Baldwin

[badge.language]: https://img.shields.io/badge/language-C%2B%2B17-yellow.svg
[badge.license]: https://img.shields.io/badge/license-MIT-blue

[language]: https://en.wikipedia.org/wiki/C%2B%2B17
[license]: https://en.wikipedia.org/wiki/MIT_License
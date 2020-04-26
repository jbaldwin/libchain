#include <iostream>

#include <chain/Chain.hpp>

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

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <chain/chain.hpp>

int main()
{
    using namespace std::string_literals;
    using namespace chain;

    static constexpr size_t ITERATIONS = 10'000'000;

    std::string input = "herp derp cherp merp derp derp"s;

    std::mutex cout_guard{};

    auto executor_func([&]() {
        {
            auto start1 = std::chrono::steady_clock::now();

            for (size_t i = 0; i < ITERATIONS; ++i)
            {
                std::string data = input;
                str::replace<str::case_t::sensitive>(data, "derp", "ferp", 2);
            }

            auto                        end1    = std::chrono::steady_clock::now();
            auto                        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
            std::lock_guard<std::mutex> g{cout_guard};
            std::cout << "replace(sensitive): " << elapsed.count() << "ms\n";
        }

        {
            auto start1 = std::chrono::steady_clock::now();

            for (size_t i = 0; i < ITERATIONS; ++i)
            {
                std::string data = input;
                str::replace<str::case_t::insensitive>(data, "DERP", "ferp", 2);
            }

            auto                        end1    = std::chrono::steady_clock::now();
            auto                        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
            std::lock_guard<std::mutex> g{cout_guard};
            std::cout << "replace(insensitive): " << elapsed.count() << "ms\n";
        }
    });

    std::vector<std::thread> workers;
    for (size_t i = 0; i < 8; ++i)
    {
        workers.emplace_back(std::thread{executor_func});
    }

    for (auto& worker : workers)
    {
        worker.join();
    }

    return 0;
}

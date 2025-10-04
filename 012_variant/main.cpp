#include <iostream>
#include <string>
#include <vector>
#include <variant>       // New include

// Define a variant type that can hold four different types
using MyVariant = std::variant<int, double, std::string, bool>;

int main(int argc, char* argv[])
{
    // A vector of variants
    std::vector<MyVariant> values;

    // For performance (optional)
    values.reserve(6);

    // Store different types
    values.emplace_back(1);                 // int
    values.emplace_back(99);                 // int
    values.emplace_back(1.23);               // double
    values.emplace_back(2.34);               // double
    values.emplace_back("Hi");  // string
    values.emplace_back(true);               // bool

    // Loop and process depending on the stored type
    for (auto &value : values)
    {

        // std::visit takes a lambda.
        // [] -> the "capture list" (no outside arguments for this lambda as [] is empty)
        // (auto&& arg) -> a forwarding reference 
        std::visit([](auto &&arg) 
        {
            using T = std::decay_t<decltype(arg)>; // deduce type

            if constexpr (std::is_same_v<T, int>)
            {
                std::cout << "int: " << arg * 2 << "\n"; // double it
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                std::cout << "double: " << arg / 2 << "\n"; // halve it
            }
            else if constexpr (std::is_same_v<T, std::string>)
            {
                std::cout << "string: " << arg + "!" << "\n"; // add exclamation
            }
            else if constexpr (std::is_same_v<T, bool>)
            {
                std::cout << "bool: " << std::boolalpha << !arg << "\n"; // flip it
            }
        }, value);
    }

    return 0;
}

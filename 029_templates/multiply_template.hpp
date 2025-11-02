#pragma once

#include <type_traits>

// C++20 concept - restricts to arithmetic types (no multiplying strings)
template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <Number T>
T multiply(T a, T b)
{
    return a * b;
}



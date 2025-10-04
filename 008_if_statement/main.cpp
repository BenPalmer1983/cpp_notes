#include <iostream>
#include <string>
#include <vector>

int main(int, char**)
{
    // if statement tutorial
    //###################################################

    // Basic IF
    std::cout << "1) Basic if ---" << std::endl;
    int a = 5;
    if (a > 0)
    {
        std::cout << "a is positive (" << a << ")" << std::endl;
    }

    // If/Else
    std::cout << "2) if / else ---" << std::endl;
    if (a % 2 == 0)
    {
        std::cout << "a is even" << std::endl;
    }
    else
    {
        std::cout << "a is odd" << std::endl;
    }


    
    // If/Else If/Else
    std::cout << "3) if / else if / else chain ---" << std::endl;
    int grade = 82;
    if (grade >= 90)
    {
        std::cout << "Grade A" << std::endl;
    }
    else if (grade >= 80)
    {
        std::cout << "Grade B" << std::endl;
    }
    else if (grade >= 70)
    {
        std::cout << "Grade C" << std::endl;
    }
    else
    {
        std::cout << "Grade D or F" << std::endl;
    }

    // Nested if
    std::cout << "--- 4) Nested if statements ---" << std::endl;
    int x = 10, y = 20;
    if (x > 0)
    {
        if (y > 0)
        {
            std::cout << "Both x and y are positive" << std::endl;
        }
    }

    // If and
    std::cout << "--- 5) if with logical operators ---" << std::endl;
    bool sunny = true;
    bool warm = false;
    if (sunny && warm)
    {
        std::cout << "Great day for the beach!" << std::endl;
    }
    else if (sunny && !warm)
    {
        std::cout << "Sunny but chilly." << std::endl;
    }
    else
    {
        std::cout << "Not sunny." << std::endl;
    }

    // Variable initialisation
    std::cout << "6) if with variable initialization (C++17+) ---" << std::endl;
    if (int n = 3; n % 2 == 1)
    {
        std::cout << "n = " << n << " is odd" << std::endl;
    }
    else
    {
        std::cout << "n is even" << std::endl;
    }


    // Compile time branching 
    // (see lambda tutorial)
    std::cout << "7) constexpr if (C++17+) ---" << std::endl;
    auto describe = [](auto v)
    {
        if constexpr (std::is_integral_v<decltype(v)>)
        {
            std::cout << v << " is an integral type" << std::endl;
        }
        else
        {
            std::cout << v << " is NOT an integral type" << std::endl;
        }
    };
    describe(42);       // integral
    describe(3.14);     // not integral


    return 0;
}

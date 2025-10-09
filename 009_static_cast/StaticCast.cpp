// =========================================================
//  Lesson: static_cast in C++
// =========================================================
//
// static_cast is the safest and most common way to convert
// between compatible types in C++.
//
// It performs conversions that are checked at compile time,
// helping to avoid accidental or unsafe type conversions.
//
// Generated with OpenAI
// =========================================================

#include <iostream>

int main()
{
    std::cout << "=== static_cast Basics ===" << std::endl;

    // -----------------------------------------------------
    // 1. Converting between numeric types
    // -----------------------------------------------------

    {        
        double pi = 3.14159;
        int pi_int = static_cast<int>(pi);   // safely converts double -> int
        std::cout << "pi as double: " << pi << std::endl;
        std::cout << "pi as int   : " << pi_int << std::endl;
        std::cout << std::endl;

        // Old-style cast (still works, but not recommended)
        int old_pi_int = (int)pi;  // works, but less clear
        std::cout << "Old-style cast result: " << old_pi_int << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 2. Converting between char and int
    // -----------------------------------------------------
    {
        char letter = 'A';
        int ascii_value = static_cast<int>(letter);
        std::cout << "Character: " << letter << "  ->  ASCII code: " << ascii_value << std::endl;

        // Convert back to char
        char next_letter = static_cast<char>(ascii_value + 1);
        std::cout << "Next character after 'A': " << next_letter << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 3. Casting pointers to void* for address display
    // -----------------------------------------------------
    {
        int number = 42;
        int* p = &number;

        std::cout << "Address of number: " << static_cast<const void*>(p) << std::endl;
        std::cout << "Value of number:   " << *p << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 4. Converting between integer and floating-point safely
    // -----------------------------------------------------
    {
        int whole = 10;
        double precise = static_cast<double>(whole) / 3; // ensures floating-point division
        std::cout << "10 divided by 3 (with static_cast): " << precise << std::endl;

        // Without static_cast, this would be integer division:
        std::cout << "10 divided by 3 (integer division): " << (whole / 3) << std::endl;
        std::cout << std::endl;
    }


    // -----------------------------------------------------
    // 5. Example of using static_cast with enum values
    // -----------------------------------------------------
    {        
        enum class Color { Red = 1, Green = 2, Blue = 3 };
        Color c = Color::Green;

        int color_value = static_cast<int>(c);
        std::cout << "Color::Green has integer value: " << color_value << std::endl;
        std::cout << std::endl;
    }
    

    std::cout << "End of program." << std::endl;
    return 0;
}






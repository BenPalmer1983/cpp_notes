#include <iostream>
#include <string>

int main(int, char**)
{
    // switch (case/select) tutorial
    //###################################################

    std::cout << "1) Basic switch over int" << std::endl;
    int code = 2;
    switch (code)
    {
        case 1:
        {
            std::cout << "code is 1" << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "code is 2" << std::endl;
            break;
        }
        default:
        {
            std::cout << "code is something else" << std::endl;
            break;
        }
    }

    std::cout << "2) Grouping cases (multiple labels)" << std::endl;
    int day = 6; // 1..7
    switch (day)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            std::cout << "Weekday" << std::endl;
            break;
        }
        case 6:
        case 7:
        {
            std::cout << "Weekend" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Invalid day" << std::endl;
            break;
        }
    }

    std::cout << "3) Fallthrough vs break" << std::endl;
    int level = 1;
    switch (level)
    {
        case 0:
        {
            std::cout << "Level 0 setup" << std::endl;
            [[fallthrough]];       // Intentional fallthrough to case 1
        }
        case 1:
        {
            std::cout << "Level 1 setup" << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "Level 2 setup" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Unknown level" << std::endl;
            break;
        }
    }

    std::cout << "4) switch on char (simple menu)" << std::endl;
    char choice = 's';
    switch (choice)
    {
        case 'n':
        {
            std::cout << "New file" << std::endl;
            break;
        }
        case 's':
        {
            std::cout << "Save file" << std::endl;
            break;
        }
        case 'q':
        {
            std::cout << "Quit" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Unknown command" << std::endl;
            break;
        }
    }

    std::cout << "5) switch with enum class (strongly-typed enums)" << std::endl;
    enum class Color { Red, Green, Blue };

    Color c = Color::Green;
    switch (c)
    {
        case Color::Red:
        {
            std::cout << "Color is Red" << std::endl;
            break;
        }
        case Color::Green:
        {
            std::cout << "Color is Green" << std::endl;
            break;
        }
        case Color::Blue:
        {
            std::cout << "Color is Blue" << std::endl;
            break;
        }
    }

    std::cout << "6) switch with initializer (C++17)" << std::endl;
    switch (int remainder = 17 % 3; remainder)
    {
        case 0:
        {
            std::cout << "17 is divisible by 3" << std::endl;
            break;
        }
        case 1:
        {
            std::cout << "17 % 3 = 1" << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "17 % 3 = 2" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Unexpected remainder" << std::endl;
            break;
        }
    }

    std::cout << "7) switch vs string note" << std::endl;
    std::string ext = "png";
    std::cout << "Extension: " << ext << std::endl;
    // Note: switch works with integral / enum types (char, int, enum class, etc.)
    // It does NOT switch on std::string. Use if/else for strings:
    if (ext == "png")
    {
        std::cout << "Image: PNG" << std::endl;
    }
    else if (ext == "jpg" || ext == "jpeg")
    {
        std::cout << "Image: JPEG" << std::endl;
    }
    else
    {
        std::cout << "Unknown/other extension" << std::endl;
    }

    std::cout << "8) Common pitfalls" << std::endl;
    // 1) Forgetting break causes unintentional fallthrough.
    // 2) Case labels must be constant expressions and unique.
    // 3) With enum class, you must qualify the enumerators (Color::Red).
    // 4) switch does not work with floating-point or std::string directly.

    std::cout << "Done: switch/case tutorial complete" << std::endl;
    return 0;
}

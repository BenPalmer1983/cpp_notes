// =========================================================
//  Lesson: Enumerations (enum and enum class) in C++
// =========================================================
//
// Enumerations (enums) let you define a new type that represents
// a fixed set of named values. They make code easier to read,
// safer, and more meaningful.
//
// =========================================================

#include <iostream>
#include <string>

int main()
{
    std::cout << "=== Enumerations (enum) ===" << std::endl;

    // -----------------------------------------------------
    // 1. Basic enum
    // -----------------------------------------------------
    //
    // An enum creates a set of named integer constants.
    //

    {
        enum Direction 
        { 
            North, 
            East, 
            South, 
            West 
        };

        Direction travel = North;

        if (travel == North)
        {
            std::cout << "Heading North!" << std::endl;
        }


        // Enum values are actually integers.
        std::cout << "Numeric value of North: " << travel << std::endl;

        // You can assign another value:
        travel = West;
        std::cout << "Now heading West (value " << travel << ")" << std::endl;
        std::cout << std::endl;

    }

    // -----------------------------------------------------
    // 2. Setting custom values
    // -----------------------------------------------------
    //
    // You can assign specific integer values to each item.
    //

    {
        enum StatusCode
        {
            OK = 200,
            NotFound = 404,
            ServerError = 500
        };

        StatusCode status = NotFound;
        std::cout << "Status code (NotFound): " << status << std::endl;
        std::cout << std::endl;
    }


    // -----------------------------------------------------
    // 3. The modern way: enum class
    // -----------------------------------------------------
    //
    // enum class provides better type safety.
    // Its values are scoped — you must prefix with the enum name.
    //

    {
        enum class Color
        {
            Red,
            Green,
            Blue
        };

        Color paint = Color::Green;

        // You can compare with another Color, but not with integers:
        if (paint == Color::Green)
        {
            std::cout << "The paint is green!" << std::endl;
        }

        // The line below would cause a compile error:
        // if (paint == 1) { }  // not allowed

        // To print its numeric value, you must cast it (static casts will be discussed shortly)
        std::cout << "Numeric value of Color::Green: "
                << static_cast<int>(paint) << std::endl;

        std::cout << std::endl;
    }


    // -----------------------------------------------------
    // 4. Example usage in a simple program
    // -----------------------------------------------------
    //
    // Enums are great for readable decision logic:
    //

    {
        enum class TrafficLight
        {
            Red,
            Yellow,
            Green
        };

        TrafficLight light = TrafficLight::Red;

        if (light == TrafficLight::Red)
        {
            std::cout << "Stop!" << std::endl;
        }
        else if (light == TrafficLight::Yellow)
        {
            std::cout << "Get ready..." << std::endl;
        }
        else
        {
            std::cout << "Go!" << std::endl;
        }

    }
    

    std::cout << std::endl;
    std::cout << "End of program." << std::endl;
    return 0;
}


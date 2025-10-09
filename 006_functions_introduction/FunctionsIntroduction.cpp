// =========================================================
//  Lesson: Introduction to Functions in C++
// =========================================================

#include <iostream>
#include <string>

// Where functions are not members of a class, they must be written in order.
// In this example main calls all the functions, so it's last.
// greet_user() calls say_hello(): say_hello() should be defined first.


// Alternatively: prototype declarations for the functions 
// This means you can define them in any order later, when the functions are implemented.
void say_hello();
void greet_user(const std::string& name);
int add_numbers(int a, int b);
std::string make_greeting(const std::string& name);





// A function that takes one parameter (void)
// The & will be explained in the next lesson.
void greet_user(const std::string& name)
{
    say_hello();
    std::cout << "Hello, " << name << "!" << std::endl;
}

// A simple function with no parameters and no return value (void)
void say_hello()
{
    std::cout << "Hello from a function!" << std::endl;
}

// A function that adds two numbers and returns the result
int add_numbers(int a, int b)
{
    int sum = a + b;
    return sum;   // send the result back to the caller
}

// A function that returns a string
std::string make_greeting(const std::string& name)
{
    return "Nice to meet you, " + name + "!";
}

// Main entry point into program
int main()
{
    std::cout << "=== Function Basics ===" << std::endl;

    // 1. Calling a simple function
    say_hello();

    // 2. Passing arguments to a function
    std::cout << "\nEnter your name: ";
    std::string user_name;

    // Read in from the user
    std::cin >> user_name;
    greet_user(user_name);

    // 3. Getting a return value from a function
    int x = 5;
    int y = 7;
    int result = add_numbers(x, y);

    std::cout << "\nThe sum of " << x << " and " << y << " is " << result << "." << std::endl;

    // 4. Using a function that returns a string
    std::string message = make_greeting(user_name);
    std::cout << message << std::endl;

    std::cout << "\nEnd of program." << std::endl;

    return 0;
}

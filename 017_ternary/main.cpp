#include <iostream>
#include <string>
#include <vector>

int main(int, char**)
{
    // basic example with string result
    //###################################################

    std::cout << "1) Basic ternary example" << std::endl;
    int a = 5;
    std::string result = (a > 0) ? "positive" : "non-positive";
    std::cout << "a = " << a << "  " << result << std::endl;

    a = 0;
    result = (a > 0) ? "positive" : "non-positive";
    std::cout << "a = " << a << "  " << result << std::endl;

    a = -1;
    result = (a > 0) ? "positive" : "non-positive";
    std::cout << "a = " << a << "  " << result << std::endl;


    // equivalent if/else
    //###################################################

    std::cout << "2) Equivalent if/else" << std::endl;
    if (a > 0)
    {
        result = "positive";
    }
    else
    {
        result = "non-positive";
    }
    std::cout << "a = " << a << "  " << result << std::endl;


    // basic example with integer result
    //###################################################

    std::cout << "3) Ternary with integers" << std::endl;
    int b = -3;
    int abs_b = (b >= 0) ? b : -b;  // absolute value
    std::cout << "b = " << b << "  abs(b) = " << abs_b << std::endl;


    // nested
    //###################################################

    std::cout << "4) Nesting ternaries " << std::endl;
    int grade = 82;
    std::string letter = (grade >= 90) ? "A" :
                         (grade >= 80) ? "B" :
                         (grade >= 70) ? "C" :
                         (grade >= 60) ? "D" : "F";
    std::cout << "grade = " << grade << "  letter grade = " << letter << std::endl;


    // equivalent if/else
    //###################################################

    std::cout << "5) Equivalent if/else grading" << std::endl;
    grade = 82;
    letter;

    if (grade >= 90)
    {
        letter = "A";
    }
    else if (grade >= 80)
    {
        letter = "B";
    }
    else if (grade >= 70)
    {
        letter = "C";
    }
    else if (grade >= 60)
    {
        letter = "D";
    }
    else
    {
        letter = "F";
    }

    std::cout << "grade = " << grade << "  letter grade = " << letter << std::endl;


    // Different return types
    //###################################################

    std::cout << "6) Ternary returning different types" << std::endl;
    // Both branches must resolve to a common type (or be convertible).
    bool flag = true;
    auto val = flag ? 3.14 : 42.0; // both double
    std::cout << "val = " << val << std::endl;

    std::cout << "7) Ternary inside loops" << std::endl;
    std::vector<int> nums {1,2,3,4,5};
    for (int n : nums)
    {
        std::cout << n << " is " << (n % 2 == 0 ? "even" : "odd") << std::endl;
    }



    // Setting a const with a ternary
    //###################################################

    std::cout << "7) Ternary for setting a const" << std::endl;

    bool int_flag {true};

    const int my_integer_1 = int_flag ? 1 : 0;
    const int my_integer_2 = int_flag ? 9 : 10;

    std::cout << int_flag << "    " << my_integer_1 << std::endl;
    std::cout << int_flag << "    " << my_integer_2 << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <memory>

int main(int, char**)
{
    // Lambdas - functor, a small inline function object
    //###################################################



    // No capture, no parameters, no return
    //###################################################

    std::cout << "1) Basic lambda: no capture, no params" << std::endl;

    auto say_hello = [] 
    { 
        std::cout << "Hello from a lambda!\n"; 
    };
    say_hello();
    std::cout << std::endl;



    // Parameters and returns
    //###################################################

    // inferred return type
    std::cout << "2) Parameters and inferred return type (int)" << std::endl;
    auto add = [](int a, int b) 
    { 
        return a + b; 
    }; 
    std::cout << "add(2, 3) = " << add(2, 3) << "\n";
    std::cout << std::endl;

    // explicit return type
    auto safe_divide = [](double x, double y) -> double 
    { 
        return y == 0.0 ? 0.0 : x / y;
    };
    std::cout << "safe_divide(10, 2) = " << safe_divide(10, 2) << "\n";
    std::cout << "safe_divide(10, 0) = " << safe_divide(10, 0) << "\n";



    // Capture lists
    //###################################################

    std::cout << "3) Capture list: [], [=], [&], and mixed." << std::endl;

    int x = 10;
    int y = 20;

    auto no_capture = [] 
    { 
        std::cout << "No capture: only local params/body" << std::endl; 
    };
    no_capture();
    

    auto by_value = [=] 
    {   
        // captures x and y by value (copies)
        std::cout << "By value: x+y = " << (x + y) << " (inside lambda)" << std::endl; 
    };    
    by_value();
    std::cout << "After by_value: x=" << x << " y=" << y << std::endl; 



    auto by_ref = [&] { // captures x and y by reference
        x += 1; y += 2;
        std::cout << "By ref:   x=" << x << " y=" << y << " (modified)\n";
    };
    by_ref();
    std::cout << "After by_ref: x=" << x << " y=" << y << std::endl; 


    auto mixed = [x, &y] { // x by value, y by reference
        // x here is a copy; y is the original
        // y will change outside; x will not
        std::cout << "Mixed: x(copy)=" << x << " y(ref)=" << y << std::endl; 
    };
    mixed();
    std::cout << "After by_ref: x=" << x << " y=" << y << std::endl; 
    std::cout << std::endl;




    // Mutable 
    //###################################################

    std::cout << "4) Mutable lambdas (modify captured-by-value)" << std::endl; 
    int counter = 0;
    auto mutable_copy = [counter]() mutable {
        // counter is a mutable copy
        counter += 5;
        std::cout << "Inside mutable lambda, counter copy = " << counter << std::endl;
    };
    mutable_copy();
    std::cout << "Original counter still = " << counter << " (unchanged)" << std::endl;
    std::cout << std::endl;



    // Capture with an initializer 
    //###################################################

    std::cout << "5) Capture with an initializer - e.g. initialise a string" << std::endl;
    int width = 3;
    auto make_padding = [pad = std::string(width, '*')](const std::string& s) 
    {
        return pad + s + pad;
    };
    std::cout << make_padding("center") << std::endl;

    // Move-only objects via init-capture
    auto ptr_src = std::make_unique<int>(42);
    auto hold_ptr = [p = std::move(ptr_src)] 
    {
        std::cout << "Unique ptr value = " << *p << "\n";
    };
    hold_ptr();
    std::cout << "ptr_src is " << (ptr_src ? "not null" : "null (moved)") << std::endl;
    std::cout << std::endl;



    // Auto parameters
    //###################################################

    std::cout << "6) Generic lambda (auto parameters)" << std::endl;
    auto print_any = [](const auto& v) 
    {
        std::cout << "print_any: " << v << "\n";
    };
    print_any(123);
    print_any(3.14159);
    print_any(std::string("hello"));

    // Forwarding reference example (perfect forwarding)
    auto forward_into = [](auto&& f, auto&& arg) 
    {
        return std::forward<decltype(f)>(f)(std::forward<decltype(arg)>(arg));
    };

    auto twice = [](int a) 
    { 
        return a * 2; 
    };
    std::cout << "forward_into(twice, 21) = " << forward_into(twice, 21) << std::endl;



    // Auto parameters
    //###################################################
    
    std::cout << "7) Lambdas with STL algorithms " << std::endl;
    std::vector<int> nums {5, 1, 4, 2, 3};

    // sort with custom comparator
    std::sort(nums.begin(), nums.end(), 
        // descending
        [](int a, int b) 
        {
            return a > b;
        }
    );
    std::cout << "Sorted desc: ";
    for (int v : nums)
    {
        std::cout << v << " ";
    } 
    std::cout << "\n";

    // transform to squares
    std::vector<int> squares(nums.size());
    std::transform(nums.begin(), nums.end(), squares.begin(), [](int v) {
        return v * v;
    });
    std::cout << "Squares:    ";
    for (int v : squares) std::cout << v << " ";
    std::cout << "\n";

    // accumulate with a lambda
    int sum = std::accumulate(nums.begin(), nums.end(), 0,
                              [](int acc, int v){ return acc + v; });
    std::cout << "Sum: " << sum << "\n";

    std::cout << "\n--- 8) Immediately-Invoked Lambda (IILE) ---\n";
    int triple_7 = [] (int n) { return n * 3; }(7);
    std::cout << "Immediate call result = " << triple_7 << "\n";

    std::cout << "\n--- 9) Returning a lambda (closure carrying state) ---\n";
    auto make_adder = [](int offset) {
        return [offset](int x) { return x + offset; };
    };
    auto add10 = make_adder(10);
    std::cout << "add10(32) = " << add10(32) << "\n";

    std::cout << "\n--- 10) Capturing this (in a small local struct demo) ---\n";
    struct Acc {
        int total{0};
        void run() {
            // capture this pointer explicitly in a lambda
            auto add_to_total = [this](int v) { total += v; };
            add_to_total(5);
            add_to_total(7);
            std::cout << "Acc.total = " << total << "\n";
        }
    } acc;
    acc.run();

    
    return 0;
}

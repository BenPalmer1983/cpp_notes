#include <iostream>
#include <stdexcept>


// 1) Basic `noexcept` on functions
void definitely_noexcept() noexcept
{
    std::cout << "Function definitely_noexcept will not throw exceptions." << std::endl;
}


void might_throw()
{
    // No noexcept spec -> potentially throwing (we won't actually throw here).
    std::cout << "Function might_throw might throw exceptions." << std::endl;
}


// 2) The `noexcept(expr)` operator
// - Evaluated at compile time. Returns true if the expression cannot throw.
int may_throw_func(int x)
{
    std::cout << "Function may_throw_func may throw exceptions, depending on x." << std::endl;
    if (x < 0) throw std::runtime_error("negative");
    return x;
}


int no_throw_func(int x) noexcept
{
    std::cout << "Function no_throw_func does not throw exceptions." << std::endl;
    return x;
}


// 3) What happens if a noexcept function throws (demo)
void declared_noexcept_but_throws() noexcept
{
    #ifdef DEMO_TERMINATE
    // If an exception escapes a noexcept function, the runtime calls std::terminate().
    throw std::runtime_error("Oops: exception escaped a noexcept function!");
    #else
    std::cout << "[DEMO_TERMINATE disabled] This function would throw and terminate if enabled." << std::endl;
    #endif
}


int main()
{
    // Section 1: Basic noexcept on functions
    std::cout << "==================== 1) Basic noexcept on functions ====================" << std::endl;
    definitely_noexcept();
    might_throw();


    std::cout << "noexcept(definitely_noexcept()) -> " << std::boolalpha << noexcept(definitely_noexcept()) << std::endl;
    std::cout << "noexcept(might_throw()) -> " << std::boolalpha << noexcept(might_throw()) << std::endl;


    // Section 2: The noexcept(expr) operator
    std::cout << std::endl;
    std::cout << "==================== 2) The noexcept(expr) operator ====================" << std::endl;
    std::cout << "noexcept(no_throw_func(42)) -> " << std::boolalpha << noexcept(no_throw_func(42)) << std::endl;
    std::cout << "noexcept(may_throw_func(42)) -> " << std::boolalpha << noexcept(may_throw_func(42)) << std::endl;
    std::cout << "Note: noexcept(...) is evaluated at compile time and does not run the code." << std::endl;


    // Section 3: If a noexcept function throws
    std::cout << std::endl;
    std::cout << "==================== 3) If a noexcept function throws ===================" << std::endl;
    std::cout << "Calling declared_noexcept_but_throws()..." << std::endl;
    try
    {
        declared_noexcept_but_throws();
        std::cout << "Returned normally (no terminate because DEMO_TERMINATE is off)." << std::endl;
    }
    catch (...)
    {
        std::cout << "You will never see this: exceptions cannot be caught if they escape a noexcept function." << std::endl;
    }


    std::cout << "To see terminate, rebuild with -DDEMO_TERMINATE." << std::endl;
    std::cout << std::endl;
    std::cout << "Done." << std::endl;
    return 0;
}
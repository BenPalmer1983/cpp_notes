
#include <iostream>
#include <string>
#include <vector>      


// Prototypes
void inspect_int(int& value);
void inspect_int_vector(std::vector<int>& v);


int main(int argc, char* argv[])
{

    //#####################
    //  Example 1
    //#####################

    // A basic loop
    std::cout << "Basic Loop" << std::endl;

    for(size_t i = 0; i< 10; i++)
    {   
        // i is only in scopt within the loop
        std::cout << i << std::endl;
    }
    std::cout << std::endl;



    //#####################
    //  Example 2
    //#####################

    // A test vector
    std::vector<int> numbers {1,2,3,4,5,6};

    std::cout << "Loop through each number   const auto& number" << std::endl;
    // Read only (const) and don't make a copy in number (&), optional: use auto (can be useful in more complicated examples)
    for(const auto& number : numbers) 
    {   
        // number is only in scope within the loop
        std::cout << number << std::endl;
    }
    std::cout << std::endl;



    //#####################
    //  Example 3
    //#####################

    // Read/Write, edit in place (&), optional: use auto (can be useful in more complicated examples)
    std::cout << "Loop through each number   auto& number and add 10" << std::endl;
    for(auto& number : numbers) 
    {   
        // number is only in scope within the loop
        number = number + 10;
    }

    std::cout << &numbers[0]  << "   " << numbers[0] << std::endl;  // 1 before loop, 11 after loop
    std::cout << &numbers[5]  << "   " << numbers[5] << std::endl;  // 6 before loop, 16 after loop
    std::cout << std::endl;



    //#####################
    //  Example 4
    //#####################

    std::cout << "Loop through each number   iterator" << std::endl;
    std::cout << "Add 10 to each" << std::endl;
    // it - iterator
    // *it - the element
    for(auto it = numbers.begin(); it != numbers.end(); it++) 
    {   
        *it = *it + 10;
    }

    std::cout << "Print out" << std::endl;
    for(auto it = numbers.begin(); it != numbers.end(); it++) 
    {   
        // print iterator location, location of actual value, the value        
        std::cout << &it << "      " << &(*it) << "      " << *it << std::endl;    
    }
    std::cout << std::endl;



    //#####################
    //  Example 5
    //#####################

    // A basic while loop - caution, as this can get stuck in an infinite loop
    std::cout << "Basic While Loop" << std::endl;

    std::size_t i = 0;
    while(i < 10)
    {   
        std::cout << i << std::endl;
        i++;                               // increment i by 1
    }
    std::cout << std::endl;


}






// Inspect
void inspect_int(int& value)
{
    std::cout << "Value: " << value << "    address: " << &value << std::endl;
}


void inspect_int_vector(std::vector<int>& v)
{
    std::cout << "[inspect_vector]\n";
    std::cout << "  address of v (the vector object) : " << &v << '\n';
    std::cout << "  v.size()                          : " << v.size() << '\n';

    // Cast v.data() to void* pointer (generic memory address) and promise not to modify data through pointer (const)
    std::cout << "  v.data() (buffer start)           : " << static_cast<const void*>(v.data()) << '\n';

    for (std::size_t i = 0; i < v.size(); i++)
    {
        std::cout << "    v[" << i << "] at " << static_cast<const void*>(&v[i])
                  << " = " << v[i] << '\n';
    }
    std::cout << '\n';
}





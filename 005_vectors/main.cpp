
#include <iostream>
#include <string>
#include <vector>               // new include

int main(int argc, char* argv[])
{

    // A vector where values will be added dynamically
    //###################################################

    
    // Create a vector of a type (e.g. doubles)

    std::cout << "Create a vector of doubles." << std::endl;

    std::vector<double> vector_of_doubles {};

    std::cout << "Size of vector_of_doubles: " << vector_of_doubles.size() << std::endl;

    
    // Add 5 items

    vector_of_doubles.reserve(5);       // Not necessary, but makes adding new elements faster

    std::cout << "Size of vector_of_doubles (after reserving): " << vector_of_doubles.size() << std::endl;


    vector_of_doubles.emplace_back(1.2);
    vector_of_doubles.emplace_back(2.3);

    std::cout << "Size of vector_of_doubles (2 items added): " << vector_of_doubles.size() << std::endl;

    vector_of_doubles.emplace_back(3.4);
    vector_of_doubles.emplace_back(4.5);
    vector_of_doubles.emplace_back(5.6);

    std::cout << "Size of vector_of_doubles (all items added): " << vector_of_doubles.size() << std::endl;

    std::cout << "Location of vector:      " << &vector_of_doubles << std::endl;
    std::cout << "Item 0:                  " << vector_of_doubles[0] << "   location :  " << &vector_of_doubles[0] << std::endl;
    std::cout << "Item 1:                  " << vector_of_doubles[1] << "   location :  " << &vector_of_doubles[1] << std::endl;
    std::cout << "Item 2:                  " << vector_of_doubles[2] << "   location :  " << &vector_of_doubles[2] << std::endl;
    std::cout << "Item 3:                  " << vector_of_doubles[3] << "   location :  " << &vector_of_doubles[3] << std::endl;
    std::cout << "Item 4:                  " << vector_of_doubles[4] << "   location :  " << &vector_of_doubles[4] << std::endl;

    std::cout << std::endl;


    // A vector with a predetermined set of values
    //###################################################

    std::cout << "Create a vector of ints, populated with values on initialization." << std::endl;
    std::vector<int> vector_with_values {8,7,6,5,4,3,2,1};


    std::cout << "Size of vector_with_values : " << vector_with_values.size() << std::endl;

    std::cout << "Location of vector:      " << &vector_with_values << std::endl;
    std::cout << "Item 0:                  " << vector_with_values[0] << "   location :  " << &vector_with_values[0] << std::endl;
    std::cout << "Item 1:                  " << vector_with_values[1] << "   location :  " << &vector_with_values[1] << std::endl;
    std::cout << "Item 2:                  " << vector_with_values[2] << "   location :  " << &vector_with_values[2] << std::endl;
    std::cout << "Item 3:                  " << vector_with_values[3] << "   location :  " << &vector_with_values[3] << std::endl;
    std::cout << "Item 4:                  " << vector_with_values[4] << "   location :  " << &vector_with_values[4] << std::endl;
    std::cout << "Item 5:                  " << vector_with_values[5] << "   location :  " << &vector_with_values[5] << std::endl;
    std::cout << "Item 6:                  " << vector_with_values[6] << "   location :  " << &vector_with_values[6] << std::endl;
    std::cout << "Item 7:                  " << vector_with_values[7] << "   location :  " << &vector_with_values[7] << std::endl;
    

    // Adding more dynamically

    vector_with_values.reserve(vector_with_values.size() + 4);  // reserve (not necessary, but useful for performance as vectors become large)
    vector_with_values.emplace_back(0);
    vector_with_values.emplace_back(-1);
    vector_with_values.emplace_back(-2);
    vector_with_values.emplace_back(-3);

    std::cout << "New size of vector_with_values : " << vector_with_values.size() << std::endl;

    std::cout << std::endl;




    // Create a vector of doubles, 100 elements, all 0.0
    //###################################################
    
    std::cout << "Create a vector of doubles, initialized with 0.0." << std::endl;
    std::vector<double> vector_zero(100);

    std::cout << "Size of vector_zero :    " << vector_zero.size() << std::endl;
    std::cout << "Item 34:                 " << vector_zero[34] << "   location :  " << &vector_zero[34] << std::endl;
    std::cout << "Item 71:                 " << vector_zero[17] << "   location :  " << &vector_zero[17] << std::endl;

    std::cout << std::endl;



    
    // Create a vector of doubles, 100 elements, all 12.3
    //###################################################

    std::cout << "Create a vector of doubles, initialized with 12.3." << std::endl;
    std::vector<double> vector_12p3(100, 12.3);

    std::cout << "Size of vector_12p3 :    " << vector_12p3.size() << std::endl;
    std::cout << "Item 34:                 " << vector_12p3[34] << "   location :  " << &vector_12p3[34] << std::endl;
    std::cout << "Item 71:                 " << vector_12p3[17] << "   location :  " << &vector_12p3[17] << std::endl;

    std::cout << std::endl;




    // Create a Matrix
    //###################################################

    size_t rows = 16;
    size_t cols = 20;

    std::cout << "Create a 2D int matrix initialised to 0." << std::endl;
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    std::cout << "Size of matrix:              " << matrix.size() << " " << matrix[0].size() << std::endl;
    std::cout << "Location of matrix:          " << &matrix << std::endl;
    std::cout << "Item [2][3]:                 " << matrix[2][3] << "   location :  " << &matrix[2][3] << std::endl;
    std::cout << std::endl;


    std::cout << "Create a 2D int matrix initialised to 99." << std::endl;
    std::vector<std::vector<int>> matrix_99(rows, std::vector<int>(cols, 99));

    std::cout << "Size of matrix_99:              " << matrix_99.size() << " " << matrix_99[0].size() << std::endl;
    std::cout << "Location of matrix_99:          " << &matrix_99 << std::endl;
    std::cout << "Item [2][3]:                    " << matrix_99[2][3] << "   location :  " << &matrix_99[2][3] << std::endl;
    std::cout << std::endl;




    // Difference between push_back and emplace_back
    //###################################################

    // Difference between push_back and emplace_back
    //###################################################

    std::cout << "Difference between push_back and emplace_back (std::string examples)." << std::endl;

    // New vector of strings where we'll add items in different ways
    std::vector<std::string> words;

    // Reserve to avoid re-allocations
    words.reserve(4);

    std::cout << "Size of words (start):   " << words.size() << std::endl;

    // 1) push_back with an existing object (copies/moves that object into the vector)
    std::string tmp = "alpha";
    words.push_back(tmp); // copies 'tmp' into the vector
    std::cout << "Added with push_back(existing obj): " << words.back() << "  " <<  words.back() << std::endl;

    // 2) push_back with a temporary (usually moves the temporary into the vector)
    words.push_back(std::string("beta")); // constructs a temporary then moves it
    std::cout << "Added with push_back(temporary):   " << words.back() << std::endl;

    // 3) emplace_back constructs the element directly in-place from constructor args
    words.emplace_back("gamma");          // constructs std::string("gamma") in-place
    std::cout << "Added with emplace_back(\"gamma\"): " << words.back() << std::endl;

    // 4) emplace_back can pass arbitrary constructor args (no temporary needed)
    words.emplace_back(3, '!');           // constructs std::string(3, '!') -> "!!!" in-place
    std::cout << "Added with emplace_back(3,'!'):    " << words.back() << std::endl;

    std::cout << "Size of words (end):     " << words.size() << std::endl;

    // Show contents and addresses of the std::string objects stored in the vector
    std::cout << "Location of words vector: " << &words << std::endl;
    for (std::size_t i = 0; i < words.size(); ++i) 
    {
        std::cout << "Item " << i << ":              "
                  << words[i]
                  << "   location :  " << &words[i] << std::endl;
    }

    std::cout << std::endl;





}







#include <iostream>
#include <string>
#include <vector>


void my_function(std::vector<int>& my_vec)
{
    std::cout << "new_vec location in function:  " << &my_vec << std::endl;  // prints 4
    std::cout << "new_vec size in function:      " << my_vec.size() << std::endl;  // prints 4

    std::cout << "   new_vec 1 at " << &my_vec[1] << " with value " << my_vec[1] << std::endl;
    std::cout << "   new_vec 2 at " << &my_vec[2] << " with value " << my_vec[2] << std::endl;
    std::cout << "   new_vec 3 at " << &my_vec[3] << " with value " << my_vec[3] << std::endl;
    std::cout << "   new_vec 4 at " << &my_vec[4] << " with value " << my_vec[4] << std::endl;
}



void matrix_function(const double (&matrix)[3][3])
{
    std::cout << "mat location in function:  " << &matrix << std::endl;  
}



int main(int argc, char* argv[])
{

    // lvalues, rvalues
    int x = 10;         // x lvalue, 10 rvalue

    std::cout << "x:                             " << x << std::endl;  // prints 10
    std::cout << "memory location of x:          " << &x << std::endl;  // prints 10


    // Can reference lvalues
    
    int& x_ref = x;

    x_ref = 20;

    std::cout << "x_ref:                         " << x_ref <<  std::endl;  // prints 20
    std::cout << "memory location of x_ref:      " << &x_ref << std::endl;  // prints 10


    //int& ref_fails = 9;    // Cannot reference an rvalue in the normal way


    //
    const int& const_ref = 5;    
    std::cout << "const_ref:                     " << const_ref << std::endl;  // prints 20
    std::cout << "const_ref location:            " << &const_ref << std::endl;  // prints 20


    int&& ref_to_rvalue = 7;    
    std::cout << "ret_to_rvalue:                 " << ref_to_rvalue << std::endl;  // prints 7
    std::cout << "ret_to_rvalue location:        " << &ref_to_rvalue << std::endl; 


    std::vector<int> vec = {1, 2, 3, 4};
    std::cout << "vec size:                      " << vec.size() << std::endl;  // prints 4
    std::cout << "vec location:                  " << &vec << std::endl; 

    std::cout << "   vec 1 at " << &vec[1] << " with value " << vec[1] << std::endl;
    std::cout << "   vec 2 at " << &vec[2] << " with value " << vec[2] << std::endl;
    std::cout << "   vec 3 at " << &vec[3] << " with value " << vec[3] << std::endl;
    std::cout << "   vec 4 at " << &vec[4] << " with value " << vec[4] << std::endl;
    std::cout << std::endl;

    std::cout << "Moving vec to new_vec" << std::endl;

    std::vector<int> new_vec = std::move(vec);
    std::cout << "vec location:                  " << &vec << std::endl;  
    std::cout << "new_vec location:              " << &new_vec << std::endl;  
    std::cout << "vec size:                      " << vec.size() << std::endl;      // prints 0
    std::cout << "new_vec size:                  " << new_vec.size() << std::endl;  // prints 4

    std::cout << "   new_vec 1 at " << &new_vec[1] << " with value " << new_vec[1] << std::endl;
    std::cout << "   new_vec 2 at " << &new_vec[2] << " with value " << new_vec[2] << std::endl;
    std::cout << "   new_vec 3 at " << &new_vec[3] << " with value " << new_vec[3] << std::endl;
    std::cout << "   new_vec 4 at " << &new_vec[4] << " with value " << new_vec[4] << std::endl;
    std::cout << std::endl;

    

    std::cout << "Passing new_vec to a function" << std::endl;
    my_function(new_vec);
    std::cout << std::endl;


    std::cout << "Creating an array" << std::endl;

    const double mat[3][3] = 
    {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    std::cout << "mat location:              " << &mat << std::endl;  


    std::cout << "Passing mat to a function" << std::endl;
    matrix_function(mat);



    return 0;
}






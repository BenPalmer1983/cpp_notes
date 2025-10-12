
#include <iostream>
#include <string>

int main()
{

    // 1.

    std::string my_string {"Favorite"};
    std::cout << "String len: " << my_string.size() << std::endl;


    // 2.

    std::string a {"C++"};
    std::string b {"is fun!"};
    std::string c = a + " " + b;


    // 3.
    std::cout << c[0] << std::endl;
    std::cout << c[c.size() - 1] << std::endl;

    // 4.
    c[c.size() - 4] = 'F';
    std::cout << c << std::endl;


    return 0;
}







#include <iostream>
#include <string>
#include <utility>  // for std::pair
#include <vector>

// Prototypes
void inspect_pair(std::pair<std::string, int>& p);
void inspect_pair_vector(std::vector<std::pair<std::string, int>>& v);


int main(int argc, char* argv[])
{
    //#####################
    //  Example 1
    //#####################

    std::cout << "Create and access std::pair" << std::endl;

    std::pair<std::string, int> person {"Alice", 30};

    std::cout << "Name: " << person.first << std::endl;
    std::cout << "Age: "  << person.second << std::endl;
    std::cout << std::endl;



    //#####################
    //  Example 2
    //#####################

    std::cout << "Modify pair values" << std::endl;

    person.first  = "Bob";
    person.second = 25;

    std::cout << "Name: " << person.first << std::endl;
    std::cout << "Age: "  << person.second << std::endl;
    std::cout << std::endl;



    //#####################
    //  Example 3
    //#####################

    std::cout << "Create vector of pairs" << std::endl;

    std::vector<std::pair<std::string, int>> people {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 40}
    };

    // Read only (const reference)
    std::cout << "Loop through each pair (const auto&)" << std::endl;
    for (const auto& p : people)
    {
        std::cout << p.first << " - " << p.second << std::endl;
    }
    std::cout << std::endl;



    //#####################
    //  Example 4
    //#####################

    std::cout << "Modify vector of pairs (auto&)" << std::endl;
    for (auto& p : people)
    {
        p.second += 5; // Everyone gets 5 years older
    }

    std::cout << "After modification:" << std::endl;
    for (const auto& p : people)
    {
        std::cout << p.first << " - " << p.second << std::endl;
    }
    std::cout << std::endl;



    //#####################
    //  Example 5
    //#####################

    std::cout << "Use iterator with vector of pairs" << std::endl;

    for (auto it = people.begin(); it != people.end(); ++it)
    {
        std::cout << "Iterator at: " << &it
                  << "   Pair address: " << &(*it)
                  << "   Values: " << it->first << " - " << it->second << std::endl;
    }
    std::cout << std::endl;



    //#####################
    //  Example 6
    //#####################

    std::cout << "Inspect with helper functions" << std::endl;
    inspect_pair(person);
    inspect_pair_vector(people);
    std::cout << std::endl;

}



// Inspect a single pair
void inspect_pair(std::pair<std::string, int>& p)
{
    std::cout << "[inspect_pair]" << std::endl;
    std::cout << "  Pair address: " << &p << std::endl;
    std::cout << "  first (" << p.first  << ") address: " << &p.first  << std::endl;
    std::cout << "  second(" << p.second << ") address: " << &p.second << std::endl;
    std::cout << std::endl;
}



// Inspect a vector of pairs
void inspect_pair_vector(std::vector<std::pair<std::string, int>>& v)
{
    std::cout << "[inspect_pair_vector]" << std::endl;
    std::cout << "  address of vector object : " << &v << std::endl;
    std::cout << "  v.size()                 : " << v.size() << std::endl;
    std::cout << "  v.data() (buffer start)  : " << static_cast<const void*>(v.data()) << std::endl;

    for (std::size_t i = 0; i < v.size(); i++)
    {
        std::cout << "    v[" << i << "] at " << static_cast<const void*>(&v[i])
                  << "   first: " << v[i].first
                  << "   second: " << v[i].second
                  << std::endl;
    }
    std::cout << std::endl;
}




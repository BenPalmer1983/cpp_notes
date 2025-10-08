#include <iostream>
#include <vector>
#include <algorithm>
#include "Zebra.hpp"


void part_4()
{

    // useful STL algorithms with integers
    //###################################################


    std::cout << "Useful STL algorithms with integers" << std::endl;
    std::cout << "###################################################" << std::endl;
    std::cout << std::endl;


    std::cout << "Create a vector of Zoo::Zebra objects" << std::endl;
    std::vector<Zoo::Zebra> herd 
    {
        Zoo::Zebra("Alice", "Zebra", 5),
        Zoo::Zebra("Bob",   "Zebra", 3),
        Zoo::Zebra("Charlie", "Zebra", 7),
        Zoo::Zebra("Daisy", "Zebra", 4)
    };

    std::cout << "Original order:" << std::endl;
    for (const auto& z : herd)
    {
        std::cout << "   " << z.get_name() << " (age " << z.get_age() << ")" << std::endl;
    }
    std::cout << std::endl;

    // Sort by name (ascending)
    std::cout << "Sort by name (ascending):" << std::endl;
    std::sort(herd.begin(), herd.end(),
              [](const Zoo::Zebra& a, const Zoo::Zebra& b)
              {
                  return a.get_name() < b.get_name();
              });

    for (const auto& z : herd)
    {
        std::cout << "   " << z.get_name() << " (age " << z.get_age() << ")" << std::endl;
    }
    std::cout << std::endl;

    // Sort by age (ascending)
    std::cout << "Sort by age (ascending):" << std::endl;
    std::sort(herd.begin(), herd.end(),
              [](const Zoo::Zebra& a, const Zoo::Zebra& b)
              {
                  return a.get_age() < b.get_age();
              });

    for (const auto& z : herd)
    {
        std::cout << "   " << z.get_name() << " (age " << z.get_age() << ")" << std::endl;
    }
    std::cout << std::endl;

    // Sort by age (descending)
    std::cout << "Sort by age (descending):" << std::endl;
    std::sort(herd.begin(), herd.end(),
              [](const Zoo::Zebra& a, const Zoo::Zebra& b)
              {
                  return a.get_age() > b.get_age();
              });

    for (const auto& z : herd)
    {
        std::cout << "   " << z.get_name() << " (age " << z.get_age() << ")" << std::endl;
    }
    std::cout << std::endl;


}
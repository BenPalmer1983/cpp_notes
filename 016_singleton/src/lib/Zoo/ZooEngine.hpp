#ifndef ZOO_ENGINE_HPP
#define ZOO_ENGINE_HPP

/*********************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Animal.hpp"
/*********************************************************************************************************************************/

namespace Zoo
{


class ZooEngine 
{

public:

    // Static function i.e. belongs to class, not an instance of the class (object)
    static void sort_by_name_asc(std::vector<Animal>& animals)
    {
        std::sort(      animals.begin(), 
                        animals.end(),
                        [](const Animal& a, const Animal& b) 
                        {
                                return a.get_name() < b.get_name();
                        } 
                );
    }

    static void sort_by_name_desc(std::vector<Animal>& animals)
    {
        std::sort(      animals.begin(), 
                        animals.end(),
                        [](const Animal& a, const Animal& b) 
                        {
                                return a.get_name() > b.get_name();
                        } 
                );
    }




    static void sort_by_age_asc(std::vector<Animal>& animals)
    {
        std::sort(      animals.begin(), 
                        animals.end(),
                        [](const Animal& a, const Animal& b) 
                        {
                                return a.get_age() < b.get_age();
                        } 
                );
    }

    static void sort_by_age_desc(std::vector<Animal>& animals)
    {
        std::sort(      animals.begin(), 
                        animals.end(),
                        [](const Animal& a, const Animal& b) 
                        {
                                return a.get_age() > b.get_age();
                        } 
                );
    }



};

}

#endif 
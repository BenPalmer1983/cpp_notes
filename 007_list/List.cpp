// =========================================================
//  Lesson: std::list in C++ (no loops)
//  Demonstrates creation, modification, and inspection
//  Includes: 
// =========================================================

/*
 * std::list
 * =========
 * Contiguous in memory: No — nodes allocated separately
 * Random access: O(n) — must traverse links
 * push_back / emplace_back: O(1)
 * push_front / emplace_front: O(1)
 * pop_back / pop_front: O(1)
 * insert (with iterator): O(1)
 * erase (with iterator): O(1)
 * Iterator invalidation: Only invalidated for erased element; others remain valid
 * Cache locality: Poor — scattered memory, pointer chasing
 * Memory overhead: High — two pointers (prev/next) per node
 * Size query: O(1) in C++11+ (cached), O(n) before
 * Splicing: O(1) — move nodes between lists without copy
 * Suitable for: Frequent insertions/deletions, stable iterators, splicing
 */

#include <iostream>
#include <string>
#include <list>

// Prototype
template <typename T>
void inspect_list(const std::list<T>& list);

int main(int argc, char* argv[])
{
    // Verbose flag
    bool verbose = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg {argv[i]};
        if (arg == "-v" || arg == "--verbose") 
        { 
            verbose = true; 
        }
    }

    // -----------------------------------------------------
    // 1. Create and inspect an empty list
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 1.\n##################################\n" << std::endl;

        std::cout << "Create an empty list of doubles." << std::endl;
        std::list<double> list;

        std::cout << "Size: " << list.size() << std::endl;
        std::cout << "Empty? " << std::boolalpha << list.empty() << "\n" << std::endl;

    }

    // -----------------------------------------------------
    // 2. Add elements (initializer list)
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 2.\n##################################\n" << std::endl;

        std::list<double> list;
        std::cout << "Add 5 elements using an initializer list." << std::endl;
        list = {1.1, 2.2, 3.3, 4.4, 5.5};

        std::cout << "Size after adding: " << list.size() << std::endl;

        // Print first and last (no loop)
        if (!list.empty())
        {
            std::cout << "First element: " << list.front() << std::endl;
            std::cout << "Last element: " << list.back() << "\n" << std::endl;
        }
        else
        {
            std::cout << "(list is empty)\n" << std::endl;
        }
    }


    // -----------------------------------------------------
    // 3. Access elements: front(), back(), and iterator
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 3.\n##################################\n" << std::endl;

        // Put 5 items in the list 
        std::list<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};

        std::cout << "Accessing elements:" << std::endl;
        if (!list.empty())
        {
            std::cout << "list.front(): " << list.front() << std::endl;
            std::cout << "list.back(): " << list.back() << "\n" << std::endl;

            // Access second element via iterator
            auto it = list.begin();
            it++;  // Move to second
            if (it != list.end())
            {
                std::cout << "Second element (via iterator): " << *it << "\n" << std::endl;
            }
        }
        else
        {
            std::cout << "Not enough elements to demonstrate access.\n" << std::endl;
        }
    }


    // -----------------------------------------------------
    // 4. Modify elements via iterator
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 4.\n##################################\n" << std::endl;

        // Put 5 items in the list 
        std::list<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};

        if (list.size() > 2)
        {
            std::cout << "Modify third element (index 2) to 99.9." << std::endl;
            auto it = list.begin();
            std::advance(it, 2);  // Move to position 2
            *it = 99.9;

            std::cout << "Check modified values:" << std::endl;
            std::cout << "First: " << list.front() << std::endl;
            std::cout << "Third (modified): " << *std::next(list.begin(), 2) << "\n" << std::endl;
        }
    }

    // -----------------------------------------------------
    // 5. pop_back() — remove last element
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 5.\n##################################\n" << std::endl;

        // Put 5 items in the list 
        std::list<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};

        if (!list.empty())
        {
            std::cout << "Remove last element with pop_back()." << std::endl;
            list.pop_back();

            std::cout << "Size after pop_back(): " << list.size() << std::endl;
            if (!list.empty())
            {
                std::cout << "New last element: " << list.back() << "\n" << std::endl;
            }
            else
            {
                std::cout << "(list is now empty)\n" << std::endl;
            }
        }
    }

    // -----------------------------------------------------
    // 6. insert() — add element in the middle
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 6.\n##################################\n" << std::endl;

        // Put 5 items in the list 
        std::list<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};

        if (list.size() >= 3)
        {
            std::cout << "Insert 123.456 before position 2." << std::endl;
            auto it = list.begin();
            std::advance(it, 2);
            list.insert(it, 123.456);

            
            if (verbose)
            {
                inspect_list(list);
            }
        }
    }


    // -----------------------------------------------------
    // 7. erase() — remove an element at a position
    // -----------------------------------------------------


    {
        std::cout << "\n\nPart 7.\n##################################\n" << std::endl;

        // Put 5 items in the list 
        std::list<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};
        if (list.size() > 1)
        {
            std::cout << "Erase element at position 1." << std::endl;
            auto it = list.begin();
            ++it;  // position 1
            list.erase(it);

            if (verbose)
            {
                inspect_list(list);
            }
        }
    }


    // -----------------------------------------------------
    // 8. clear() — remove all elements
    // -----------------------------------------------------


    {
        std::cout << "\n\nPart 8.\n##################################\n" << std::endl;

        // Put 5 items in the list 
        std::list<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};

        std::cout << "Clear all elements with clear()." << std::endl;
        list.clear();

        std::cout << "Size after clear(): " << list.size() << std::endl;
        std::cout << "Empty? " << std::boolalpha << list.empty() << "\n" << std::endl;
    }


    // -----------------------------------------------------
    // 9. List initialized with values (ints)
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 9.\n##################################\n" << std::endl;

        std::cout << "Create a new list with initial values." << std::endl;
        std::list<int> numbers {10, 20, 30, 40, 50};

        std::cout << "numbers size: " << numbers.size() << std::endl;
        std::cout << "First: " << numbers.front() << ", Last: " << numbers.back() << "\n" << std::endl;

        if (verbose)
        {
            inspect_list(numbers);
        }
    }


    // -----------------------------------------------------
    // 10. Insert, erase, and push_front on integer list
    // -----------------------------------------------------

    {
        std::cout << "\n\nPart 10.\n##################################\n" << std::endl;

        std::cout << "Create a new list with initial values." << std::endl;
        std::list<int> numbers {10, 20, 30, 40, 50};


        if (verbose)
        {
            inspect_list(numbers);
        }

        if (numbers.size() >= 3)
        {
            // Insert before index 2
            auto it = numbers.begin();
            std::advance(it, 2);
            numbers.insert(it, 99);
            std::cout << "After insert before index 2: ";
            auto check = numbers.begin();
            std::advance(check, 2);
            std::cout << "numbers[2] = " << *check << std::endl;
            std::cout << "Size: " << numbers.size() << std::endl;

            // Erase at index 4
            if (numbers.size() > 4)
            {
                auto erase_it = numbers.begin();
                std::advance(erase_it, 4);
                numbers.erase(erase_it);
                std::cout << "After erase at index 4: ";
                std::cout << "Size: " << numbers.size() << std::endl;
                std::cout << "First: " << numbers.front() << ", Last: " << numbers.back() << "\n" << std::endl;
            }
            else
            {
                std::cout << "(not enough elements to erase index 4)\n" << std::endl;
            }
        }

        // Bonus: push_front
        std::cout << "Add 5 to front with push_front()." << std::endl;
        numbers.push_front(5);
        std::cout << "New first: " << numbers.front() << std::endl;

        if (verbose)
        {
            inspect_list(numbers);
        }
        
    }

    // -----------------------------------------------------
    // End of program
    // -----------------------------------------------------
    std::cout << "End of list demonstration." << std::endl;
    return 0;
}


// =========================================================
// Definition of inspect_list (no loops)
// =========================================================


template <typename T>
void inspect_list(const std::list<T>& list)
{
    std::cout << "[inspect_list]\n";
    std::cout << "  address of list (object) : " << &list << '\n';
    std::cout << "  list.size()              : " << list.size() << '\n';

    if (list.empty())
    {
        std::cout << "  (list is empty)\n";
    }
    else
    {
        std::cout << "  Elements: ";
        for (auto it = list.begin(); it != list.end(); it++)
        {
            std::cout << "    " << static_cast<const void*>(&(*it)) << "   " << *it << std::endl;
        }
        std::cout << '\n';
        std::cout << "  front() = " << list.front() << '\n';
        std::cout << "  back()  = " << list.back() << '\n';
    }

    std::cout << '\n';
}

#include <iostream>
#include <unordered_map>
#include "CustomHashTable.hpp"




int main()
{


    // Using the built in unordered_map
    {

        // Create a hash table: string -> int
        std::unordered_map<std::string, int> ages;

        // Insert
        ages["Alice"] = 25;
        ages["Bob"] = 30;
        ages.emplace("Charlie", 35);  // Alternative

        // Update
        ages["Alice"] = 26;

        // Lookup
        if (auto it = ages.find("Bob"); it != ages.end()) 
        {
            std::cout << "Bob is " << it->second << " years old." << std::endl;
        }

        // Check existence
        if (ages.contains("David")) 
        {  // C++20
            std::cout << "David found." << std::endl;
        } 
        else 
        {
            std::cout << "David not found." << std::endl;
        }

        // Delete
        ages.erase("Charlie");

        // Iterate
        std::cout << "All entries:\n";
        for (const auto& [name, age] : ages) 
        { 
            std::cout << "  " << name << ": " << age << "\n";
        }

        // Size and bucket info (advanced)
        std::cout << "Size: " << ages.size() << "\n";
        std::cout << "Buckets: " << ages.bucket_count() << "\n";
        std::cout << "Load factor: " << ages.load_factor() << "\n";

    }

    std::cout << std::endl;

    {
        CustomHashTable<std::string, int> ages;
        ages.set_verbose(true);

        // Using the insert method
        ages.insert("Alice",   25);
        ages.insert("Bob",     30);
        ages.insert("Charlie", 35);
        ages.insert("David",   40);
        ages.insert("Eve",     22);
        ages.insert("Frank",   45);
        ages.insert("Grace",   28);
        ages.insert("Hannah",  33);
        ages.insert("Isaac",   29);
        ages.insert("Julia",   31);
        ages.insert("Kevin",   27);
        ages.insert("Linda",   38);
        ages.insert("Michael", 42);
        ages.insert("Nina",    26);
        ages.insert("Oliver",  34);
        ages.insert("Paula",   39);
        ages.insert("Quinn",   23);
        ages.insert("Ryan",    36);

        // Using the [] overload
        ages["Sophia"]    = 30;
        ages["Thomas"]    = 41;
        ages["Uma"]       = 24;
        ages["Victor"]    = 37;
        ages["Willow"]    = 32;
        ages["Xander"]    = 29;
        ages["Yara"]      = 35;
        ages["Zara"]      = 40;
        
        std::cout << "\n\nAccess using []\n\n";
        std::cout << ages["Sophia"] << std::endl;

        
        std::cout << "\n\nList all the names and ages\n\n";

        for (const auto& [name, age] : ages) 
        {
            std::cout << "  " << name << ": " << age << "\n";
        }
        std::cout << std::endl;

        {
            auto it = ages.begin();
            std::cout << (*it).first << ":  " << (*it).second << "\n";
        }

        {
            auto it = ages.begin();
            std::cout << it->first << ":  " << it->second << "\n";
        }

        
    }

    


    return 0;
}






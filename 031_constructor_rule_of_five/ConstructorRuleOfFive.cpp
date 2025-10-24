// =========================================================
//  Lesson: Rule of Five — Copying and Moving in C++
//  Demonstrates: defaulted constructors and assignments
//  Generated with OpenAI (GPT-5)
// =========================================================

#include <iostream>
#include <string>
#include <utility>
#include <vector>



// ---------------------------------------------------------
//  Class: Zebra
// ---------------------------------------------------------
//  This class demonstrates the rule of five:
//   1) Regular constructor
//   2) Copy constructor
//   3) Move constructor
//   4) Copy assignment
//   5) Move assignment
// ---------------------------------------------------------

class Zebra
{
private:
    std::string _name;
    size_t _age {};
    std::string _description;

public:

    // The Rule of Five

    // 1) Regular constructor
    // Creating a new object from scratch (using name, age)
    Zebra(const std::string& name, const size_t age, const std::string& description)  // 1) Regular 
        : _name(name), _age(age), _description(description)
    {
        std::cout << "##Default Constructor## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
    }


    // 2) Copy constructor            
    // Copying from another object (other)
    Zebra(const Zebra& other)
        : _name(other._name), _age(other._age), _description(other._description)
    {
        std::cout << "##Copy Constructor## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
    }
    // Same as (without printing):   Zebra(const Zebra&) = default;  


    // 3) Move constructor
    // Moves from existing Zebra
    Zebra(Zebra&& other) noexcept
        : _name(std::move(other._name)), _age(std::move(other._age)), _description(std::move(other._description))
    {
        std::cout << "##Move Constructor## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        other._age = 0;
    }
    // Same as (without printing):   Zebra(Zebra&&) noexcept = default;


    // 4) Copy assignment operator
    // An existing Zebra is replaced by copying from another (other)
    Zebra& operator=(const Zebra& other)
    {
        if (this != &other) 
        {
            _name = other._name;
            _age = other._age;
            _description = other._description;
            std::cout << "##Copy Assignment## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        }
        return *this;
    }
    // Same as (without printing):   Zebra& operator=(const Zebra&) = default;


    // 5) Move assignment operator
    // An existing Zebra is replaced by moving from another (other)
    Zebra& operator=(Zebra&& other) noexcept
    {
        if (this != &other) 
        {
            _name = std::move(other._name);
            _age = std::move(other._age);
            _description = std::move(other._description);
            std::cout << "##Move Assignment## (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        }
        return *this;
    }
    // Same as (without printing):   Zebra& operator=(Zebra&&) noexcept = default;


    

    // Destructor 
    ~Zebra()
    {
        std::cout << "##Destructor## Zebra (" << _name << " at " << std::hex << this << std::dec << ")" << std::endl;
        _name.clear(); 
        _age = 0;
        _description.clear(); 
    }

    // Helper function to print info
    void display(const std::string& msg = "") const
    {
        std::cout << "  " << msg << "  " << _name << " (age " << _age << ")" << std::endl;
    }

    const std::string& get_name() const { return _name; }
    size_t get_age() const { return _age; }


    friend void inspect_zebra(const Zebra& z, const std::string& name)
    {
        std::cout << "[inspect_zebra]\n";
        std::cout << "  Zebra variable: " << name << "\n";

        // Address of the Zebra object itself
        std::cout << "  address of z (the Zebra object)     : " << &z << '\n';

        // Address of each member variable
        std::cout << "  address of _name member             : " << static_cast<const void*>(&(z._name)) << '\n';
        std::cout << "  address of _age  member             : " << &(z._age) << '\n';
        std::cout << "  address of _description member      : " << static_cast<const void*>(&(z._description)) << '\n';


        // Size and contents
        std::cout << "  _age                                : " << z._age << '\n';
        std::cout << "  _name value                         : " << z._name << '\n';
        std::cout << "  _name.size()                        : " << z._name.size() << '\n';
        std::cout << "  _description value                  : " << z._description << '\n';
        std::cout << "  _description.size()                 : " << z._description.size() << '\n';

        // For the std::string variables - where the characters are stored
        std::cout << "  _name.data() (string buffer)        : "
                << static_cast<const void*>(z._name.data()) << '\n';
        std::cout << "  _description.data() (string buffer) : "
                << static_cast<const void*>(z._description.data()) << '\n';

        std::cout << '\n';
    }

};

// ---------------------------------------------------------
//  Main
// ---------------------------------------------------------

int main()
{
    std::cout << "=== Rule of Five Demonstration ===" << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 1) Constructing
    // -----------------------------------------------------

    std::cout << "-----------------------------------------------------" <<std::endl;
    std::cout << "1) Construct z1 and z2" <<std::endl;
    std::cout << "-----------------------------------------------------" <<std::endl;
    std::cout << "Creating 2 Zebras (Zippy, Arthur).  This will call the Default Constructor for each.\n" <<std::endl;
    Zebra z1 {"Zippy", 5, "This is a longer description for the Zebra (Zippy)."};
    Zebra z2 {"Arthur", 7, "This is a longer description for the Zebra (Arthur)."};

    inspect_zebra(z1, "z1");
    inspect_zebra(z2, "z2");


    std::cout << std::endl;
    std::cout << "Two distinct Zebras have been created in memory." << std::endl;
    std::cout << "These have been created in the scope of main() so will be accessible throughout." << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 2) Copy construction
    // -----------------------------------------------------

    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "2) copy construction:" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "copy Zippy z1 to z3" <<std::endl;
        inspect_zebra(z1, "z1");
        std::cout << "copying...with Zebra z3 {z1};" <<std::endl;
        Zebra z3 {z1};           // invokes copy constructor        
        z3.display("Copied from");
        inspect_zebra(z3, "z3");
    }

    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "2) copy construction:" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "copy Zippy z1 to z3" <<std::endl;
        inspect_zebra(z1, "z1");
        std::cout << "copying...Zebra z3 = z1;" <<std::endl;
        Zebra z3 = z1;           // invokes copy constructor        
        z3.display("Copied from");
        inspect_zebra(z3, "z3");
    }
    std::cout << std::endl;
    std::cout << "Copied the contents of z1 to z3.  Notice z3 destroyed when it went out of scope." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 3) Move construction
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "3) move construction:" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "create a temporary Zebra and move to z4" <<std::endl;
        Zebra z5 {"Forrest", 8, "This is a much longer string to describe Forrest, the Zebra, to ensure it's stored on the heap and not the stack."};
        z5.display("Move construction");
        inspect_zebra(z5, "z5");
        Zebra z4 = std::move(z5);
        z4.display("Move construction");
        inspect_zebra(z4, "z4");
        inspect_zebra(z5, "z5");
    }
    std::cout << std::endl;
    std::cout << "Move constructed Zebra to Z4." << std::endl;
    std::cout << "Name is on the stack due to it's small size." << std::endl;
    std::cout << "Description is on the heap as it's larger." << std::endl;
    std::cout << "Notice the description.data() address is the same for z5 and z4." << std::endl;
    std::cout << "The compiler only moves what is large enough to be worth moving." << std::endl;
    std::cout << "The second print of z5 has been cleared." << std::endl;
    std::cout << "Notice z4 and z5 destroyed when out of scope." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 4) Copy assignment
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "4) copy assignment (=):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "copy z2 to z4" <<std::endl;
        Zebra z4 {Zebra{"Bertha", 8, ""}};
        inspect_zebra(z4, "z4");
        z4 = z2;   // replaces contents of z4 with z2
        z4.display("After copy assignment from");
        inspect_zebra(z2, "z2");
        inspect_zebra(z4, "z4");
    }
    std::cout << std::endl;
    std::cout << "Notice that the original z4 is overwritten with a copy of z2." << std::endl;
    std::cout << "Notice that z4 is destroyed when it goes out of scope." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 5) Move assignment
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "5) Move assignment (std::move):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "move z1 to z4" <<std::endl;
        inspect_zebra(z1, "z1");
        Zebra z4 = std::move(z1);   // moves z1 into z4
        z4.display("After move assignment from");
        inspect_zebra(z4, "z4");
        inspect_zebra(z1, "z1");
    }
    std::cout << std::endl;
    std::cout << "Notice that the original z4 is created from z1." << std::endl;
    std::cout << "In the process, z1 has been reset with _description moved to z4." << std::endl;
    std::cout << "Memory location for z4 _description is the same as z1 _description." << std::endl;
    std::cout << "Notice that z4 is destroyed when it goes out of scope." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 6) Using with std::vector
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "Vector demonstration (copies/moves inside container):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::vector<Zebra> pen;
        pen.reserve(4); // reserve to avoid reallocation during inserts


        std::cout << std::endl;
        std::cout << "Emplace Daisy (construct in place):" << std::endl;
        pen.emplace_back("Daisy", 4, "");                 // constructs in-place   Default constructor
        std::cout << std::endl;

        std::cout << "Emplace Daisy (construct then move):" << std::endl;
        pen.emplace_back(Zebra{"Charlie", 3, ""});        // temporary -> move     Default constructor then move
        std::cout << "Notice default constructor -> move -> destructor for temporary" << std::endl;
        std::cout << std::endl;


        std::cout << "Push Ernie (construct then move):" << std::endl;
        pen.push_back(Zebra("Ernie", 6, ""));             // temporary -> move     Default constructor then move
        std::cout << "Notice default constructor -> move -> destructor for temporary" << std::endl;
        std::cout << std::endl;
        
        std::cout << "Emplace Fiona (construct in place):" << std::endl;
        pen.emplace_back("Fiona", 9, "");                 // constructs in-place   Default constructor
        std::cout << std::endl;

        
        std::cout << std::endl;
        std::cout << "Zebras in pen:" << std::endl;
        for (const auto& z : pen)
        {
            z.display("Stored");
        }

        std::cout << std::endl;
        std::cout << "Zebras in pen:" << std::endl;
        size_t i {};
        for (const auto& z : pen)
        {
            i++;
            inspect_zebra(z, "z" + std::to_string(i));
        }
    }
    std::cout << std::endl;
    std::cout << "Notice that the original z4 is created from z1." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "=== End of program ===" << std::endl;
    return 0;
}




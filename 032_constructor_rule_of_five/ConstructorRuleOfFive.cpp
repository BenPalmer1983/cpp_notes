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
//  This class demonstrates:
//   - Regular constructor
//   - Copy constructor
//   - Move constructor
//   - Copy assignment
//   - Move assignment
//   - and how =default keeps compiler-generated behavior
// ---------------------------------------------------------

class Zebra
{
private:
    std::string _name;
    size_t _age {};

public:
    // 1) Regular constructor
    Zebra(const std::string& name, size_t age)  // 1) Regular 
        : _name(name), _age(age)
    {
        std::cout << "Constructing Zebra: " << _name << " (age " << _age << ")" << std::endl;
    }

    // 2) The Rule of Five: explicitly keep default behavior
    Zebra(const Zebra&) = default;                 // 2) Copy constructor
    Zebra(Zebra&&) noexcept = default;             // 3) Move constructor      noexcept - promise that function won't let any exceptions escape/must be caught
    Zebra& operator=(const Zebra&) = default;      // 4) Copy assignment
    Zebra& operator=(Zebra&&) noexcept = default;  // 5) Move assignment

    // Optional destructor (not needed here, but shown for completeness)
    ~Zebra()
    {
        std::cout << "Destroying Zebra: " << _name << std::endl;
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
        std::cout << "  " << name << "\n";

        // Address of the Zebra object itself
        std::cout << "  address of z (the Zebra object)   : " << &z << '\n';

        // Address of each member variable
        std::cout << "  address of _name member           : " << static_cast<const void*>(&(z._name)) << '\n';
        std::cout << "  address of _age  member           : " << &(z._age) << '\n';

        // For the std::string, we can show its internal buffer address.
        // (This is where the actual characters are stored.)
        std::cout << "  _name.data() (string buffer)      : "
                << static_cast<const void*>(z.get_name().data()) << '\n';

        // Size and contents
        std::cout << "  _name.size()                      : " << z._name.size() << '\n';
        std::cout << "  _age                              : " << z._age << '\n';
        std::cout << "  _name value                       : " << z._name << '\n';

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
    std::cout << "Construct z1 and z2" <<std::endl;
    std::cout << "-----------------------------------------------------" <<std::endl;
    Zebra z1 {"Zippy", 5};
    Zebra z2 {"Arthur", 7};

    inspect_zebra(z1, "z1");
    inspect_zebra(z2, "z2");

    std::cout << std::endl;
    std::cout << std::endl;

    // -----------------------------------------------------
    // 2) Copy construction
    // -----------------------------------------------------

    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "Copy construction:" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "copy z1 to z3" <<std::endl;
        inspect_zebra(z1, "z1");
        Zebra z3 {z1};           // invokes copy constructor
        z3.display("Copied from");
        inspect_zebra(z3, "z3");
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 3) Move construction
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "Move construction (temporary object):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "move construction to z4" <<std::endl;
        Zebra z4 {Zebra{"Bertha", 8}};   // temporary -> moved
        z4.display("Moved from temporary");
        inspect_zebra(z4, "z4");
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 4) Copy assignment
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "Copy assignment (=):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "copy z2 to z4" <<std::endl;
        Zebra z4 = z2;   // replaces contents of z4 with z2
        z4.display("After copy assignment from");
        inspect_zebra(z2, "z2");
        inspect_zebra(z4, "z4");
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 5) Move assignment
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "Move assignment (std::move):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "move z1 to z4" <<std::endl;
        inspect_zebra(z1, "z1");
        Zebra z4 = std::move(z1);   // moves z1 into z4
        z4.display("After move assignment from");
        inspect_zebra(z1, "z1");
        inspect_zebra(z4, "z4");
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // -----------------------------------------------------
    // 6) Using with std::vector
    // -----------------------------------------------------
    {
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::cout << "Vector demonstration (copies/moves inside container):" << std::endl;
        std::cout << "-----------------------------------------------------" <<std::endl;
        std::vector<Zebra> pen;
        pen.reserve(4); // reserve to avoid reallocation during inserts

        pen.emplace_back("Daisy", 4);                 // constructs in-place
        pen.emplace_back(Zebra{"Charlie", 3});        // temporary -> move
        pen.push_back(Zebra("Ernie", 6));             // temporary -> move
        pen.emplace_back("Fiona", 9);                 // constructs in-place

        std::cout << "\nZebras in pen:" << std::endl;
        for (const auto& z : pen)
        {
            z.display("Stored");
        }

        std::cout << "\nZebras in pen:" << std::endl;
        size_t i {};
        for (const auto& z : pen)
        {
            i++;
            inspect_zebra(z, "z" + std::to_string(i));
        }
    }

    std::cout << std::endl;
    std::cout << "=== End of program ===" << std::endl;
    return 0;
}




#include <iostream>
#include <string>
#include <string_view>   // for std::string_view
#include <charconv>      // for std::from_chars

int main()
{
    // 1) Creating strings
    {
        std::cout << "Create an empty string." << std::endl;
        std::string empty {};
        std::cout << "empty: \"" << empty << "\" (size = " << empty.size() << ")\n" << std::endl;

        std::cout << "Create a string with text." << std::endl;
        std::string hello {"Hello"};
        std::cout << "hello: " << hello << " (size = " << hello.size() << ")\n" << std::endl;

        std::cout << std::endl;
    }

    // 2) Concatenation
    {
        std::string hello {"Hello"};
        std::string world {"World"};

        std::cout << "Concatenate two strings." << std::endl;
        std::string message = hello + ", " + world + "!";
        std::cout << "message: " << message << "\n" << std::endl;
        
        std::cout << std::endl;
    }


    // 3) Indexing (like arrays)
    {
        std::string message {"Hello World"};

        std::cout << "Access individual characters (0-based)." << std::endl;
        std::cout << "message[0]: " << message[0] << std::endl;
        std::cout << "message[7]: " << message[7] << "\n" << std::endl;
        
        std::cout << std::endl;
    }


    // 4) Changing contents
    {
        std::string message {"Hello World"};
        std::cout << "Change characters by index." << std::endl;
        message[0] = 'h';
        std::cout << "modified message: " << message << "\n" << std::endl;
        
        std::cout << std::endl;
    }

    // 5) String methods
    {
        std::cout << "Append" << std::endl;
        std::string sentence = "This is a great string.";
        std::cout << "String: " << sentence << std::endl;
        sentence.append(" But it could be better!");
        std::cout << "String after append: " << sentence << std::endl;

        auto pos_1 = sentence.find("strings");
        std::cout << "find 'could': position " << pos_1 << std::endl;

        auto pos_2 = sentence.find("COULD");
        std::cout << "find 'COULD': position " << pos_2 << std::endl;
        std::cout << "End position (COULD not found): " << std::string::npos << std::endl;


        std::string sub = sentence.substr(4, 7); // start=4, length=7
        std::cout << "substr(4,7): " << sub << "\n" << std::endl;
    }


    // 6) Conversion between numbers and strings
    {
        std::cout << "Convert number to string and back." << std::endl;
        int number = 123;
        std::string num_str = std::to_string(number);
        std::cout << "to_string(123): " << num_str << std::endl;

        int parsed = std::stoi("456");
        std::cout << "stoi(\"456\"): " << parsed << "\n" << std::endl;
    }


    // 7) Mixing with C-style strings
    {
        std::cout << "argv-style char* to std::string." << std::endl;
        const char* cstr = "command_line_argument";
        std::string modern_str {cstr};
        std::cout << "Converted: " << modern_str << "\n" << std::endl;
    }


    // 8) string_view — lightweight read-only string wrapper
    {
        std::string string_to_view {"This is a string to view."}; 

        std::cout << "string_view example (no copy)." << std::endl;
        std::string_view sv = string_to_view;
        std::cout << "string_view: " << sv << " (size = " << sv.size() << ")\n" << std::endl;

        // sv does not own the memory. If modern_str is destroyed, sv becomes invalid
    }



    // 9) from_chars — fast numeric parsing
    {
        std::cout << "from_chars example (parsing integers)." << std::endl;
        std::string text_number {"123456789"};
        std::string_view text_number_sv = text_number;

        int value {};
        auto [ptr, ec] = std::from_chars(text_number_sv.data(), text_number_sv.data() + text_number_sv.size(), value);

        if (ec == std::errc()) 
        {
            std::cout << "Parsed number: " << value << std::endl;
        } 
        else 
        {
            std::cout << "Parsing failed!" << std::endl;
        }

        std::cout << "First unparsed char (ptr): '" 
                << ((ptr != text_number_sv.data() + text_number_sv.size()) ? *ptr : ' ') 
                << "'\n" << std::endl;
    }


    // 10) from_chars — fast numeric parsing (fails)
    {
        std::string text_number {"1234A56789"};
        std::string_view text_number_sv = text_number;

        int value {};
        auto [ptr, ec] = std::from_chars(text_number_sv.data(), text_number_sv.data() + text_number_sv.size(), value);

        if (ec == std::errc()) 
        {
            std::cout << "Parsed number: " << value << std::endl;
        } 
        else 
        {
            std::cout << "Parsing failed!" << std::endl;
        }
        std::cout << "First unparsed char (ptr): '" 
                << ((ptr != text_number_sv.data() + text_number_sv.size()) ? *ptr : ' ') 
                << "'\n" << std::endl;
    }

    return 0;
}





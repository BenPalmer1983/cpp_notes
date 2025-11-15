
#include <iostream>
#include <regex>
#include <sstream>


std::string load_text();


int main()
{
    std::string test_text = load_text();

    // Example 1: find all standalone 3-digit numbers in the entire text
    {
        std::regex three_digits(R"(\b\d{3}\b)");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), three_digits), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[3-digit] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }

    // Example 2: find all 2 digit 2 letter.
    {
        std::regex two_digit_two_alpha(R"(\d{2}[A-Za-z]{2})");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), two_digit_two_alpha), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[2-digit 2-alpha] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }

    // Example 3: find all 2 letter 3 digit 2 letter.
    {
        std::regex find_2a3d2a(R"(\b([A-Za-z]{2})(\d{3})([A-Za-z]{2})\b)");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), find_2a3d2a), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[2-alpha 3-digit 2-alpha] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }

    // Example 4: find all 2 digit 3 letter 2 digit.
    {
        std::regex find_2d3a2d(R"(\b(\d{2})([A-Za-z]{3})(\d{2})\b)");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), find_2d3a2d), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[2-digit 3-alpha 2-digit] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }

    // Example 5: find all 2 digit * letter 2 digit.
    {
        std::regex find_2d3a2d(R"(\b(\d{2})([A-Za-z]*)(\d{2})\b)");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), find_2d3a2d), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[2-digit *-alpha 2-digit] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }

    // Example 6: find all 2 digit, *letter or digit, 2 digit.
    {
        std::regex find_pattern(R"(\b(\d{2})([A-Za-z\d]*)(\d{2})\b)");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), find_pattern), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[2-digit *-alpha/digit 2-digit] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }

    // Example 7: find all 2 digit, *letter or space, 2 digit.
    {
        std::regex find_pattern(R"(\b(\d{2})([A-Za-z\s]*)(\d{2})\b)");
        for (std::sregex_iterator it(test_text.begin(), test_text.end(), find_pattern), end; it != end; it++) 
        {
            const auto& m = *it;
            std::cout << "[2-digit *-alpha/space 2-digit] " << m.str() << " at pos " << m.position() << std::endl;
        }
    }





    return 0;
}






std::string load_text()
{
    return 
"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed vitae risus ac lectus ullamcorper aliquet. Integer nec velit vitae magna blandit commodo. Suspendisse potenti. Curabitur non nunc non lorem laoreet bibendum. Praesent id urna sit amet nibh vulputate dictum. Donec iaculis, augue et feugiat fermentum, arcu dui lobortis ipsum, eget ultrices arcu ipsum at nisl. Vivamus sodales, odio id accumsan finibus, est justo hendrerit nibh, id vestibulum augue lorem in urna.\n\nPhasellus dignissim, tellus non efficitur ullamcorper, enim sem viverra arcu, id iaculis neque tortor id magna. In laoreet, nibh non scelerisque efficitur, felis augue congue lectus, vitae euismod massa odio sit amet mauris. Vestibulum at risus nec risus tincidunt porta. Integer sodales, ante vel faucibus finibus, arcu ex tristique eros, id pharetra nisi lorem in ex. Proin non varius massa. Cras id massa vitae justo fermentum tincidunt. Mauris semper, neque a luctus cursus, nibh metus mollis felis, a commodo lorem enim quis mi.\n\n123\n234\n345\n12abc34\n\naa123aa\n\nDonec vel imperdiet lorem. Sed at commodo eros, non condimentum nibh. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. 12aa Nullam scelerisque, massa non ultrices volutpat, velit lectus ultricies lacus, eu tristique felis nisl quis nibh. Abcd123ghaaa aaa aa. Aliquam vitae dictum lorem. Maecenas a luctus diam. Sed sagittis, lorem vel varius venenatis, 12abcdefg34 est est 12ab  cd34 aliquet nibh, 12ab1cd34 12ab1a1cd34 vel tristique justo nulla at nunc.";


}




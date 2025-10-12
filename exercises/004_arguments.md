# C++ Exercises — Command Line Arguments  
*Generated with OpenAI (GPT-5)*  

---

## Overview

These exercises are based on **Arguments.cpp** and introduce the handling of command-line arguments in C++.  
You will learn how to access arguments passed when the program is launched, convert them to strings, and perform basic processing.

---

## Concepts

- `int argc` — argument count  
- `char* argv[]` — argument vector  
- Program name in `argv[0]`  
- Conversion from C-style strings to `std::string`  
- Using loops to iterate through arguments  
- Conditional checks on argument count  

---

## Exercises

1. **Print the program name**  
   Modify the code so that it prints only the program name (`argv[0]`) on a single line.

2. **Count and list arguments**  
   Display both the **total number of arguments** (`argc`) and list them all with their indices.

3. **Check for user input**  
   If at least one user argument is provided, print:  
   ```
   First argument: <value>
   ```
   Otherwise, print `"No user arguments."`

4. **Use arguments as data**  
   Accept two numbers from the command line and print their sum.  
   *Hint:* Convert them from strings using `std::stoi()`.

5. **Conditional options**  
   If the user runs the program with `--help`, print a short usage guide, for example:  
   ```
   Usage: ./program <arg1> <arg2> [options]
   ```

6. **Optional verbose mode**  
   Add a flag `-v` or `--verbose` that enables extra output when present.

7. **Echo all arguments**  
   Write a loop to print all arguments on a single line, separated by spaces.

8. **Argument length**  
   Print the length (number of characters) of each argument.

9. **String conversion practice**  
   Create a `std::vector<std::string>` from `argv` and print the contents using a range-based `for` loop.

10. **Advanced: argument inspection**  
    Print each argument’s **index**, **value**, and **address** using  
    `static_cast<const void*>(argv[i])` to display the pointer location.

---

## Extension

Try combining string and numeric conversions:  
Accept arguments like `--repeat 5 hello` and print the word `"hello"` five times.

---

*End of file — generated with OpenAI (GPT-5)*

# C++ Exercises — Strings  
*Generated with OpenAI (GPT-5)*  

---

## Overview

These exercises are based on **Strings.cpp** and explore modern C++ string handling, including concatenation, indexing, methods, and conversions.

---

## Concepts

- `std::string` creation and modification  
- String concatenation and indexing  
- String methods (`find`, `substr`, `append`)  
- Conversion between strings and numbers  
- `std::string_view` and `std::from_chars`

---

## Exercises

1. **String basics**  
   Create a string with your favorite word and print its length.

2. **Concatenation**  
   Combine two strings, e.g. `"C++"` and `"is fun!"`, into one sentence.

3. **Indexing**  
   Print the first and last characters of your string using `[]`.

4. **Modify a string**  
   Change one character (for example, make it uppercase) using indexing.

5. **Substring extraction**  
   Use `.substr()` to extract a portion of your string.

6. **Find a word**  
   Use `.find()` to check if a substring (like `"fun"`) exists inside another string.

7. **Convert numbers ↔ strings**  
   - Use `std::to_string()` to convert an integer to a string.  
   - Use `std::stoi()` to convert `"123"` back to an integer.

8. **C-style string to `std::string`**  
   Convert a `const char*` like `"example"` into a `std::string` and print it.

9. **String view practice**  
   Create a `std::string_view` from an existing string and print its contents and size.

10. **`from_chars` test**  
    Try parsing `"12345"` using `std::from_chars`.  
    Then try `"12a45"` — what happens?

---

## Extension

Experiment with string concatenation performance:  
Compare `+` versus `.append()` for combining strings.



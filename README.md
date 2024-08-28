
# Roman Numeral and Arabic Digit Converter

This program is a C++ implementation that reads a file containing Roman numerals and Arabic digits, validates them, converts between the two formats, sorts them, and allows the user to search for specific values. The results can be printed to both the console and a file.

## Features

- **Validation:** Ensures that the Roman numerals and Arabic digits are valid.
- **Conversion:** Converts Roman numerals to Arabic digits and vice versa.
- **Linked List Management:** Dynamically manages a linked list to store the converted values.
- **Sorting:** Provides sorting options by either Roman numerals or Arabic digits.
- **Searching:** Allows the user to search for a specific Roman numeral or Arabic digit.
- **File Output:** Writes the sorted list to a file named `numbers.txt`.

## Usage

1. **Compile the Program:**
   ```bash
   g++ -o roman_arabic_converter main.cpp
   ```

2. **Run the Program:**
   ```bash
   ./roman_arabic_converter
   ```

3. **Input:**
   - Enter the name of the file containing the Roman numerals and Arabic digits.

4. **Menu Options:**
   - `1. Search`: Search for a Roman numeral or Arabic digit in the list.
   - `2. Sort`: Sort the list by Roman numerals or Arabic digits.
   - `3. Exit`: Exit the program.

5. **Output:**
   - The sorted list is printed to the console and saved to `numbers.txt`.

## Example File Format

The input file should contain lines of Roman numerals and Arabic digits in the following format:

```
XIII   13
IV      4
XC     90
```

Each line must have the Roman numeral first, followed by its corresponding Arabic digit.

## Functions Overview

- **createNode:** Creates a new node with Roman numerals and Arabic digits.
- **validity:** Validates the Roman numerals and Arabic digits.
- **conRoman:** Converts Arabic digits to Roman numerals.
- **conArabic:** Converts Roman numerals to Arabic digits.
- **outputfx:** Writes the sorted list to `numbers.txt`.
- **SearchFunction:** Searches for a specific Roman numeral or Arabic digit in the list.
- **PrintFx:** Prints the sorted list based on the selected criterion.
- **merge:** Merges two sorted sublists.
- **mergeSort:** Recursively divides and sorts the list.
- **finalPrint:** Recursively prints the final sorted list to the console.

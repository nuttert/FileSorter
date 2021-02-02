#include <iostream>
#include <chrono>

#include "Generator/Generator.hpp"
#include "StringSorter/Sorter.hpp"

int main()
{
    using namespace std::chrono_literals;
    using namespace std::string_literals;

    Generator generator{true};
    generator.Generate(10000, 5, "./GeneratedData/test_digits.txt");

    StringsSorter sorter(3);
    sorter.Sort("./GeneratedData/test_digits.txt", "./GeneratedData/test_digits_sorted.txt");

    return 0;
}
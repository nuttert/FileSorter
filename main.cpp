#include <iostream>
#include <chrono>

#include "Generator/Generator.hpp"
#include "StringSorter/Sorter.hpp"

int main()
{
    using namespace std::chrono_literals;
    using namespace std::string_literals;

    Generator generator{true};
    generator.Generate(10000000, 100, "./GeneratedData/test_digits.txt");

    StringsSorter sorter(1000);
    sorter.Sort("./GeneratedData/test_digits.txt", "./GeneratedData/test_digits_sorted.txt");

    return 0;
}
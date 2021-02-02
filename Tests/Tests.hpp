#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include "Generator.hpp"
#include "Sorter.hpp"

TEST(Sorter, test_1)
{
    Generator generator{true};
    generator.Generate(100, 5, "./GeneratedData/test_digits.txt");

    StringsSorter sorter(3);
    sorter.Sort("./GeneratedData/test_digits.txt", "./GeneratedData/test_digits_sorted.txt");

    std::ifstream sorted("./GeneratedData/test_digits_sorted.txt");
    std::ifstream unsorted("./GeneratedData/test_digits.txt");

    std::string line;
    std::vector<std::string> auto_sorted_buffer;
    std::vector<std::string> sorted_buffer;

    if (!sorted.is_open())
        std::runtime_error("Couldn't open input file");
    if (!unsorted.is_open())
        std::runtime_error("Couldn't open input file");
    
    while (!sorted.eof())
    {
        while (std::getline(sorted, line) && !line.empty())
            auto_sorted_buffer.push_back(line);
        
    }
    while (!unsorted.eof())
    {
        while (std::getline(unsorted, line) && !line.empty())
            sorted_buffer.push_back(line);
        std::sort(sorted_buffer.begin(), sorted_buffer.end());
    }

    ASSERT_EQ(auto_sorted_buffer, sorted_buffer);
}

TEST(Sorter, test_2)
{
    Generator generator{false};
    generator.Generate(100, 5, "./GeneratedData/test_symbols.txt");

    StringsSorter sorter(10);
    sorter.Sort("./GeneratedData/test_symbols.txt", "./GeneratedData/test_symbols_sorted.txt");

    std::ifstream sorted("./GeneratedData/test_symbols_sorted.txt");
    std::ifstream unsorted("./GeneratedData/test_symbols.txt");

    std::string line;
    std::vector<std::string> auto_sorted_buffer;
    std::vector<std::string> sorted_buffer;

    if (!sorted.is_open())
        std::runtime_error("Couldn't open input file");
    if (!unsorted.is_open())
        std::runtime_error("Couldn't open input file");
    
    while (!sorted.eof())
    {
        while (std::getline(sorted, line) && !line.empty())
            auto_sorted_buffer.push_back(line);
        
    }
    while (!unsorted.eof())
    {
        while (std::getline(unsorted, line) && !line.empty())
            sorted_buffer.push_back(line);
        std::sort(sorted_buffer.begin(), sorted_buffer.end());
    }

    ASSERT_EQ(auto_sorted_buffer, sorted_buffer);
}